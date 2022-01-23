/*
 * @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
 * @date Created 2022-01-20
*/

#ifndef COLLATZ_CLI_NUMBER_SEARCH_H
#define COLLATZ_CLI_NUMBER_SEARCH_H

#include <cstdint>
#include <optional>
#include <tuple>

#include "common.h"

namespace number_search {

std::tuple<bool, uint64_t, std::size_t> find_number_simple(const uint_t limit);

/**
 * @return
 * true; number with the largest sequence length, while being less then limit,
 * if it can correctly found; length of such sequence.
 * false; start number at which overflow happens otherwise; zero.
 */
std::tuple<bool, uint64_t, std::size_t> find_number(const uint_t limit);

}

#endif //COLLATZ_CLI_NUMBER_SEARCH_H
