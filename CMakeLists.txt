##
#  @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
#  @date Created 2022-01-20
#

cmake_minimum_required(VERSION 3.15)

project(collatz_cli VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

# "STD"/"OPT"
set(BUILD_TYPE "OPT")

set(HEADERS
    src/common.h
    src/handle_input.h
    src/number_search.h
    $<$<STREQUAL:${BUILD_TYPE},OPT>:src/number_search_optimized.h>
)

set(SOURCES
    src/main.cpp
    src/handle_input.cpp
    $<$<STREQUAL:${BUILD_TYPE},STD>:src/number_search_simple.cpp>
    $<$<STREQUAL:${BUILD_TYPE},OPT>:src/number_search_optimized.cpp>
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC
    # BUILD_TYPE_${BUILD_TYPE}
)
