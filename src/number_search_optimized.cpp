/**
 * @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
 * @date Created 2022-01-20
 * @date Updated 2022-01-24
 */

#include <string>
#include <future>
#include <thread>

#include "number_search.h"
#include "number_search_optimized.h"

// class PSOSequenceLengthCounter

SequenceLengthCounter::SequenceLengthCounter() :
        _precomputation({1, 0, 0, ONE_IS_UNREACHABLE}) {
    for (std::size_t i = 1; i < PRECOMPUTATION_SIZE; ++i)
        _precomputation[i] = precompute(i);
}

std::size_t SequenceLengthCounter::count(const uint_t start_value) const {
    std::size_t sequence_length{1};
    uint_t t{start_value};

    while (t != 1) {
        uint_t a = t >> K_SCALE_FACTOR;

        if (a == 0) {
            if (_precomputation[t]._steps_to_1 != ONE_IS_UNREACHABLE) {
                sequence_length += _precomputation[t]._steps_to_1;
                break;
            }
            sequence_length += K_SCALE_FACTOR + _precomputation[t]._c;
            t = _precomputation[t]._d;
        } else {
            uint_t b = t - (a << K_SCALE_FACTOR);

            try {
                t = safe_add(safe_multiply(
                    _precomputation[b]._c_power_of_3, a),
                        _precomputation[b]._d);
            } catch (const std::overflow_error &error) {
                throw std::overflow_error(
                    "SequenceLengthCounter::count(" +
                    to_string(start_value)+ ")");
            }

            sequence_length += K_SCALE_FACTOR + _precomputation[b]._c;
        }
    }

    return sequence_length;
}

SequenceLengthCounter::PrecomputationItem
        SequenceLengthCounter::precompute(uint_t value) {
    std::size_t steps_left{K_SCALE_FACTOR};
    std::size_t increases_count{0};

    while (steps_left && value != 1) {
        std::size_t value_ctz = ctz<uint_t>(value);
        if (value_ctz >= steps_left) {
            value >>= steps_left;
            steps_left = 0;
            break;
        }
        value >>= value_ctz;
        steps_left -= value_ctz;

        if (value == 1)
            break;

        const uint_t value_next = value + (value >> 1) + 1;

        value = value_next;
        ++increases_count;
        --steps_left;
    }

    if (value != 1)
        return {
            uint_pow(uint_t{3},increases_count),
            value,
            increases_count,
            ONE_IS_UNREACHABLE};

    const std::size_t steps_to_1{K_SCALE_FACTOR - steps_left + increases_count};
    increases_count += (steps_left + 1) >> 1;
    value = (steps_left & 1) ? 2 : 1;

    return {
        uint_pow(uint_t{3}, increases_count),
        value,
        increases_count,
        steps_to_1};
}

// end class PSOSequenceLengthCounter

static std::tuple<uint_t, std::size_t> find_number_modulo(
        const uint_t limit,
        const uint_t divisor,
        const uint_t modulo,
        const SequenceLengthCounter &sequenceLengthCounter) {
    uint_t max_sequence_number{1};
    std::size_t max_sequence_length{1};

    for (uint_t i{(modulo) ? modulo : divisor}; i < limit; i += divisor) {
        std::size_t steps_count =
                sequenceLengthCounter.count(i);

        if (steps_count > max_sequence_length) {
            max_sequence_length = steps_count;
            max_sequence_number = i;
        }
    }

    return {max_sequence_number, max_sequence_length};
}

namespace number_search {

std::tuple<uint64_t, std::size_t> find_number(const uint_t limit) {
    SequenceLengthCounter sequenceLengthCounter;

    uint_t max_sequence_number{1};
    std::size_t max_sequence_length{1};

#ifndef USE_MULTITHREADING
    std::tie(max_sequence_number, max_sequence_length) =
        find_number_modulo(limit, 1, 1, sequenceLengthCounter);
#else
    const std::size_t concurrency = std::thread::hardware_concurrency() - 1;

    std::vector<std::future<std::tuple<uint_t, std::size_t>>> search_futures;
    for (std::size_t i{0}; i < concurrency; ++i)
        search_futures.push_back(
            std::async(std::launch::async, &find_number_modulo,
                limit, concurrency, i, std::ref(sequenceLengthCounter)));

    for (std::size_t i{0}; i < concurrency; ++i) {
        uint_t sequence_number{0};
        std::size_t sequence_length{0};
        std::tie(sequence_number, sequence_length) =
            search_futures[i].get();
        if (sequence_length > max_sequence_length || (
                sequence_length == max_sequence_length &&
                sequence_number < max_sequence_number)) {
            max_sequence_length = sequence_length;
            max_sequence_number = sequence_number;
        }
    }
#endif
    return {max_sequence_number, max_sequence_length};
}

}
