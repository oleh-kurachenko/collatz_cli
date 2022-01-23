/*
 * @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
 * @date Created 2022-01-20
*/

#ifndef COLLATZ_CLI_COMMON_H
#define COLLATZ_CLI_COMMON_H

#include <cstdint>
#include <stdexcept>

typedef uint64_t uint_t;

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
UINT_T uint_pow(UINT_T base, std::size_t power) {
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
