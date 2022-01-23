/*
 * @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
 * @date Created 2022-01-20
*/

#ifndef COLLATZ_CLI_HANDLE_INPUT_H
#define COLLATZ_CLI_HANDLE_INPUT_H

#include <optional>
#include <string_view>
#include <limits>

namespace handle_input {

template<typename UINT_T>
std::optional<UINT_T> parse_input(const std::string_view);

template<typename UINT_T>
constexpr UINT_T limit() {
    return std::numeric_limits<UINT_T>::max();
}

template<>
std::optional<uint64_t> parse_input(const std::string_view);

}

#endif //COLLATZ_CLI_HANDLE_INPUT_H
