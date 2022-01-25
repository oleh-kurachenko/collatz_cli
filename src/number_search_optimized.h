/*
 * @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
 * @date Created 2022-01-21
 * @date Updated 2022-01-23
 */

#ifndef COLLATZ_CLI_NUMBER_SEARCH_OPTIMIZED_H
#define COLLATZ_CLI_NUMBER_SEARCH_OPTIMIZED_H

#include <vector>
#include <tuple>
#include <limits>

#include "common.h"

/**
 * Parity sequence optimized sequence length counter.
 *
 * @see https://en.wikipedia.org/wiki/Collatz_conjecture#Time%E2%80%93space_tradeoff
 */
class SequenceLengthCounter {
public:
    SequenceLengthCounter();
    SequenceLengthCounter(const SequenceLengthCounter &) = delete;
    SequenceLengthCounter operator=(const SequenceLengthCounter &) = delete;
    ~SequenceLengthCounter() = default;

    [[nodiscard]] std::size_t count(const uint_t start_value) const;

private:
    struct PrecomputationItem {
        uint_t _c_power_of_3;
        uint_t _d;
        std::size_t _c;
        std::size_t _steps_to_1;
    };

    static constexpr std::size_t K_SCALE_FACTOR{2};
    static constexpr std::size_t PRECOMPUTATION_SIZE{1 << K_SCALE_FACTOR};
    static constexpr std::size_t ONE_IS_UNREACHABLE{
        std::numeric_limits<std::size_t>::max()};

    std::array<PrecomputationItem, PRECOMPUTATION_SIZE> _precomputation;

    /**
     * Precompute segment for given start value
     *
     * @param value - start value
     * @return tuple, which contains:
     *     - 3 in power c
     *     - d
     *     - number of steps to reach 1 (or special value K_SCALE_FACTOR if
     *         it would not be reached in less than K_SCALE_FACTOR steps)
     *
     * @note this function is NOT overflow-safe. It's correctness is dependent
     * on the value of K_SCALE_FACTOR.
     */
    [[nodiscard]] static PrecomputationItem precompute(uint_t value);
};

#endif //COLLATZ_CLI_NUMBER_SEARCH_OPTIMIZED_H
