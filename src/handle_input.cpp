/*
 * @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
 * @date Created 2022-01-20
*/

#include <string>

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

}