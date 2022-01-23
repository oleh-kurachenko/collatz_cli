/*
 * @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
 * @date Created 2022-01-20
*/

#include <iostream>

#include "common.h"
#include "handle_input.h"
#include "number_search.h"

int main(const int argc, const char *const *const argv) {
    if (argc != 2) {
        std::cerr
            << "Bad arguments: should be single positive integer"
            << std::endl;
        return 1;
    }

    std::optional<uint_t> input_number =
        handle_input::parse_input<uint_t>(argv[1]);
    if (!input_number) {
        std::cerr
            << "Bad argument: should be positive integer, less or equal to "
            << handle_input::limit<uint_t>()
            << std::endl;
        return 2;
    }

    std::tuple<bool, uint64_t, std::size_t> max_sequence_number =
        number_search::find_number(input_number.value());

    if (!std::get<0>(max_sequence_number)) {
        std::cerr
            << "Integer overflow during computation at sequence starting with "
            << std::get<1>(max_sequence_number)
            << ", aborting"
            << std::endl;
        return 3;
    }

    std::cout
        << "Sequence with maximum length starts with: "
        << std::get<1>(max_sequence_number)
        << ", sequence length: "
        << std::get<2>(max_sequence_number)
        << std::endl;
    return 0;
}
