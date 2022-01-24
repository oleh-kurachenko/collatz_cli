/**
 * @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
 * @date Created 2022-01-20
 * @date Updated 2022-01-24
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

    uint_t max_sequence_number{0};
    std::size_t max_sequence_length{0};

    try {
        std::tie(max_sequence_number, max_sequence_length) =
            number_search::find_number(input_number.value());
    } catch (const std::overflow_error &error) {
        std::cerr
            << "Integer overflow during computation at "
            << error.what()
            << ", aborting."
            << std::endl;
        return 3;
    } catch (...) {
        std::cerr
            << "Unexpected error during max sequence computation"
            << std::endl;
        return 127;
    }

    std::cout
        << "Sequence with maximum length starts with: "
        << max_sequence_number
        << ", sequence length: "
        << max_sequence_length
        << std::endl;
    return 0;
}
