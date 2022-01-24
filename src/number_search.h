/**
 * @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
 * @date Created 2022-01-20
 * @date Updated 2022-01-24
 */

#ifndef COLLATZ_CLI_NUMBER_SEARCH_H
#define COLLATZ_CLI_NUMBER_SEARCH_H

#include <cstdint>
#include <optional>
#include <tuple>

#include "common.h"

namespace number_search {

/**
 * @return
 * number with the largest sequence length, while being less then limit start
 * number; length of those sequence.
 *
 * @throws std::overflow_error
 */
std::tuple<uint64_t, std::size_t> find_number(const uint_t limit);

}

#endif //COLLATZ_CLI_NUMBER_SEARCH_H
