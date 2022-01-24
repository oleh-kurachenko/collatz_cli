/**
 * @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
 * @date Created 2022-01-20
 * @date Updated 2022-01-24
 */

#include <string>
#include <algorithm>

#include "handle_input.h"

namespace handle_input {

template<>
std::optional<uint64_t> parse_input(const std::string_view input_string) {
    if (input_string.empty())
        return std::nullopt;

    const std::string input_string_s(input_string);
    std::size_t input_number_length{0};
    try {
        const uint64_t input_number =
            std::stoull(input_string_s, &input_number_length);
        if (input_string.length() == input_number_length && input_number != 0)
            return input_number;
    } catch (...) { }

    return std::nullopt;
}

#if defined(__GNUC__) && defined(__BYTE_ORDER__) && \
    (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
template<>
std::optional<__uint128_t> parse_input(const std::string_view input_string) {
    if (input_string.empty()
            || !std::all_of(input_string.begin(),
                input_string.end(), &isdigit)
            || input_string.length() > 38)
        throw std::invalid_argument(
                "parse_input(" + std::string(input_string) + ")");

    __uint128_t result = 0;
    __uint128_t t = 1;

    for (std::size_t i{0}; i < input_string.length(); ++i, t *= 10)
        result += (input_string[input_string.length() - i - 1] - '0') * t;

    return result;
}
#endif

}