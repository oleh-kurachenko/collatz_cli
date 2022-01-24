/**
 * @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
 * @date Created 2022-01-20
 * @date Updated 2022-01-24
 */

#ifndef COLLATZ_CLI_COMMON_H
#define COLLATZ_CLI_COMMON_H

#include <cstdint>
#include <stdexcept>
#include <iostream>

// uint_t

#if defined(USE_UINT128) && defined(__GNUC__) && defined(__BYTE_ORDER__) && \
    (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
typedef __uint128_t uint_t;

union Uint128Manipulator {
    __uint128_t u128;
    struct {
        uint64_t _1;
        uint64_t _2;
    } u64;
};

std::string to_string(__uint128_t value);

inline std::ostream &operator<<(std::ostream &ostream, __uint128_t value) {
    return (ostream << to_string(value));
}
#else
typedef uint64_t uint_t;
using std::to_string;
#endif

// ctz

/**
 * ctz stands for "count trailing zeroes" in binary form of number.
 *
 * For example ctz(100101000b) = 3; ctz(10b) = 1; ctz(11111100b) = 2
 *
 * @tparam UINT_T
 * @return count of trailing zeroes in binary form of parameter
 */
template <typename UINT_T>
static std::size_t ctz(UINT_T);

template <typename UINT_T>
static std::size_t ctz_implementation(UINT_T v) {
    std::size_t c{0};

    while (!(v & 1)) {
        v = v >> 1;
        ++c;
    }

    return c;
}

template <>
inline std::size_t ctz(const unsigned long v) {
#if defined(__clang__) || defined(__GNUC__)
    return __builtin_ctzl(v);
#else
    return ctz_implementation(v);
#endif
}

template <>
inline std::size_t ctz(const unsigned long long v) {
#if defined(__clang__) || defined(__GNUC__)
    return __builtin_ctzll(v);
#else
    return ctz_implementation(v);
#endif
}

#if defined(USE_UINT128) && defined(__GNUC__) && defined(__BYTE_ORDER__) && \
    (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
template <>
inline std::size_t ctz(const __uint128_t v) {
    const Uint128Manipulator uint128_manip{v};

    if (uint128_manip.u64._1 == 0)
        return ctz<uint64_t>(uint128_manip.u64._2) + 64;

    return ctz<uint64_t>(uint128_manip.u64._1);
}
#endif

// overflow-safe operations

template <typename UINT_T>
UINT_T safe_add(const UINT_T, const UINT_T);

template <>
inline unsigned long safe_add(const unsigned long p1, const unsigned long p2) {
    unsigned long result{0};

#if defined(__clang__) || defined(__GNUC__)
    if (__builtin_uaddl_overflow(p1, p2, &result))
        throw std::overflow_error("safe_add(...)");
#else
    NOT IMPLEMENTED
#endif

    return result;
}

template <>
inline unsigned long long safe_add(
        const unsigned long long p1, const unsigned long long p2) {
    unsigned long long result{0};

#if defined(__clang__) || defined(__GNUC__)
    if (__builtin_uaddll_overflow(p1, p2, &result))
        throw std::overflow_error("safe_add(...)");
#else
    NOT IMPLEMENTED
#endif

    return result;
}

#if defined(USE_UINT128) && defined(__GNUC__) && defined(__BYTE_ORDER__) && \
    (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
template <>
inline __uint128_t safe_add(const __uint128_t p1, const __uint128_t p2) {
    if (std::numeric_limits<__uint128_t>::max() - p2 < p1)
        throw std::overflow_error("safe_add(...)");
    return p1 + p2;
}
#endif

template <typename UINT_T>
UINT_T safe_multiply(const UINT_T, const UINT_T);

template <>
inline unsigned long safe_multiply(
        const unsigned long p1, const unsigned long p2) {
    unsigned long result{0};

#if defined(__clang__) || defined(__GNUC__)
    if (__builtin_umull_overflow(p1, p2, &result))
        throw std::overflow_error("safe_multiply(...)");
#else
    NOT IMPLEMENTED
#endif

    return result;
}

template <>
inline unsigned long long safe_multiply(
        const unsigned long long p1, const unsigned long long p2) {
    unsigned long long result{0};

#if defined(__clang__) || defined(__GNUC__)
    if (__builtin_umulll_overflow(p1, p2, &result))
        throw std::overflow_error("safe_multiply(...)");
#else
    NOT IMPLEMENTED
#endif

    return result;
}

#if defined(USE_UINT128) && defined(__GNUC__) && defined(__BYTE_ORDER__) && \
    (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
template <>
inline __uint128_t safe_multiply(const __uint128_t p1, const __uint128_t p2) {
    if (std::numeric_limits<__uint128_t>::max() / p2 < p1)
        throw std::overflow_error("safe_multiply(...)");
    return p1 * p2;
}
#endif

// utils

/**
 * Raise base to power
 *
 * @note this function is NOT overflow-safe
 *
 * @tparam UINT_T
 * @param base
 * @param power
 * @return base raised to power
 */
template <typename UINT_T>
constexpr UINT_T uint_pow(UINT_T base, std::size_t power) {
    UINT_T result{1};

    while (power) {
        if (power & 1) {
            result *= base;
            --power;
        } else {
            base *= base;
            power >>= 1;
        }
    }

    return result;
}

#endif //COLLATZ_CLI_COMMON_H
