/**
 * @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
 * @date Created 2022-01-24
 */

#include "common.h"

std::string to_string(__uint128_t value) {
    static constexpr std::size_t HIGHEST_POWER_OF_10_IN_UINT128{38};
    static constexpr __uint128_t highest_digit_const =
            uint_pow<__uint128_t>(10, HIGHEST_POWER_OF_10_IN_UINT128);

    if (value == 0)
        return "0";

    __uint128_t highest_digit{highest_digit_const};
    std::size_t result_length{HIGHEST_POWER_OF_10_IN_UINT128 + 1};
    while (highest_digit > value) {
        highest_digit /= 10;
        --result_length;
    }

    std::string result(result_length, '_');
    std::size_t i = 0;
    while (highest_digit != 0) {
        result[i] = char('0' + value / highest_digit);
        value %= highest_digit;
        highest_digit /= 10;
        ++i;
    }

    return result;
}
