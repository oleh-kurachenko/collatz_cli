/*
 * @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
 * @date Created 2022-01-20
 * @date Updated 2022-01-21
 */

#include "number_search.h"

/**
 * @return sequence length for given start number, if it can correctly
 * found, std::nullopt otherwise
 */
static std::optional<std::size_t> count_steps(const uint_t start_number) {
    std::size_t sequence_length{1};
    uint_t t(start_number);

    while (t != 1) {
        // Getting ctz (see common.h) of t to find out how many times it has to
        // be divided by 2 to get odd number
        std::size_t t_ctz = ctz<uint_t>(t);
        // Divide ctz by 2^t_ctz using right shift, equivalent to t_ctz
        // consecutive divisions
        t >>= t_ctz;
        sequence_length += t_ctz;

        if (t == 1)
            break;

        // Equivalent to (3 * t + 1) / 2 in natural numbers
        const uint_t t_next = t + (t >> 1) + 1;

        // Checking for overflow
        if (t_next < t)
            return std::nullopt;

        sequence_length += 2;
        t = t_next;
    }

    return sequence_length;
}

namespace number_search {

std::tuple<bool, uint64_t, std::size_t> find_number(const uint_t limit) {
    uint_t max_sequence_number{1};
    std::size_t max_sequence_length{1};

    for (uint_t i = 2; i <= limit; ++i) {
        std::optional<std::size_t> steps_count = count_steps(i);

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
