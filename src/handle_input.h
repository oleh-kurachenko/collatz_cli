/**
 * @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
 * @date Created 2022-01-20
 * @date Updated 2022-01-24
 */

#ifndef COLLATZ_CLI_HANDLE_INPUT_H
#define COLLATZ_CLI_HANDLE_INPUT_H

#include <optional>
#include <string_view>
#include <limits>

#include "common.h"

namespace handle_input {

template <typename UINT_T>
UINT_T parse_input(const std::string_view);

template <typename UINT_T>
constexpr UINT_T limit() {
    return std::numeric_limits<UINT_T>::max();
}

template <>
constexpr __uint128_t limit() {
    return uint_pow<__uint128_t>(10, 38) - 1;
}

template<>
uint64_t parse_input(const std::string_view);

#if defined(__GNUC__) && defined(__BYTE_ORDER__) && \
    (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
template<>
__uint128_t parse_input(const std::string_view);
#endif

}

#endif //COLLATZ_CLI_HANDLE_INPUT_H
