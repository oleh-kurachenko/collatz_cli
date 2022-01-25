##
#  @author Oleh Kurachenko <oleh.kurachenko@gmail.com>
#  @date Created 2022-01-20
#  @date Updated 2022-01-25
#

cmake_minimum_required(VERSION 3.15)

project(collatz_cli VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

# "STD"/"OPT"
if(NOT DEFINED BUILD_TYPE)
    set(BUILD_TYPE "OPT")
endif()
# "YES"/"NO"
if(NOT DEFINED USE_MULTITHREADING)
    set(USE_MULTITHREADING "YES")
endif()
# "YES"/"NO"
if(NOT DEFINED USE_UINT128)
    set(USE_UINT128 "YES")
endif()

set(HEADERS
    src/common.h
    src/handle_input.h
    src/number_search.h
    $<$<STREQUAL:${BUILD_TYPE},OPT>:src/number_search_optimized.h>
)

set(SOURCES
    src/main.cpp
    src/common.cpp
    src/handle_input.cpp
    $<$<STREQUAL:${BUILD_TYPE},STD>:src/number_search_simple.cpp>
    $<$<STREQUAL:${BUILD_TYPE},OPT>:src/number_search_optimized.cpp>
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC
    $<$<STREQUAL:${USE_MULTITHREADING},YES>:USE_MULTITHREADING>
    $<$<STREQUAL:${USE_UINT128},YES>:USE_UINT128>
)

if(BUILD_TYPE STREQUAL "OPT" AND USE_MULTITHREADING STREQUAL "YES")
    target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC pthread)
endif()
