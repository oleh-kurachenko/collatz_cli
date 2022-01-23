/*
 * @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
 * @date Created 2022-01-20
*/

#include <string>

// TODO remove
#include <iostream>

#include "number_search.h"
#include "number_search_optimized.h"

// class PSOSequenceLengthCounter

SequenceLengthCounter::SequenceLengthCounter() :
        _c(PRECOMPUTATION_SIZE, 0),
        _c_power_of_3(PRECOMPUTATION_SIZE, 1),
        _d(PRECOMPUTATION_SIZE, 0),
        _steps_to_1(PRECOMPUTATION_SIZE, ONE_IS_UNREACHABLE) {

//    std::cout << "- PRECOMPUTATION_SIZE: " << PRECOMPUTATION_SIZE << std::endl;
    for (std::size_t i = 1; i < PRECOMPUTATION_SIZE; ++i) {
//        if (i == 421886)
//            std::cout << "- i: " << i << std::endl;
        std::tie(_c[i], _c_power_of_3[i], _d[i], _steps_to_1[i]
            ) = precompute(i);
    }
}

std::size_t SequenceLengthCounter::count(const uint_t start_value) {
    //std::cout << "- count(" << start_value << ")" << std::endl;

    std::size_t sequence_length{1};
    uint_t t{start_value};

    while (t != 1) {
        uint_t a = t >> K_SCALE_FACTOR;

        if (a == 0) {
            if (_steps_to_1[t] != ONE_IS_UNREACHABLE) {
                sequence_length += _steps_to_1[t];
                break;
            }
            sequence_length += K_SCALE_FACTOR + _c[t];
            t = _d[t];
        } else {
            uint_t b = t - (a << K_SCALE_FACTOR);

            t = safe_add(safe_multiply(
                    _c_power_of_3[b], a), _d[b]);
            sequence_length += K_SCALE_FACTOR + _c[b];
        }
    }

    return sequence_length;
}

std::tuple<std::size_t, uint_t, uint_t, std::size_t>
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
        return {increases_count, uint_pow(uint_t{3}, increases_count),
            value, ONE_IS_UNREACHABLE};

    increases_count += (steps_left + 1) >> 1;
    value = (steps_left & 1) ? 2 : 1;

    return {increases_count, uint_pow(uint_t{3}, increases_count), value,
        K_SCALE_FACTOR - steps_left + increases_count};
}

// end class PSOSequenceLengthCounter

namespace number_search {

std::tuple<bool, uint64_t, std::size_t> find_number(const uint_t limit) {
    SequenceLengthCounter sequenceLengthCounter;

    uint_t max_sequence_number{1};
    std::size_t max_sequence_length{1};

    for (uint_t i = 2; i <= limit; ++i) {
        std::optional<std::size_t> steps_count =
            sequenceLengthCounter.count(i);

        if (!steps_count)
            return {false, i, 0};

        if (steps_count.value() > max_sequence_length) {
            max_sequence_length = steps_count.value();
            max_sequence_number = i;
        }
    }

    return {true, max_sequence_number, max_sequence_length};
}

}
