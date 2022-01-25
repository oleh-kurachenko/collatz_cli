# collatz_cli

CLI tool for searching number m in range 1..n, so there lenght of Collatz
sequence is the biggest among others. This is a test task. Generally, I'm
quite sceptical about doing test tasks during job search, but I've found
Collatz problem quite interesting, so here it is.

## Problem desctiption

### General

Write two programs that find the starting number below a given limit that has
the longest Collatz sequence. The program should be called with a single
number as the command line parameter. This number is the upper limit below
which the longest chain should be found. Note that intermediate steps may go
above this upper limit. Program one will optimise for code simplicity and low
memory usage. Program two sacrifices some simplicity and memory for
significant reduction in CPU time required.

### Collatz sequence definition

The following iterative sequence is defined for the set of positive integers:

```
n → n/2 (n is even)
n → 3n + 1 (n is odd)
```

Using the rule above and starting with 13, we generate the following sequence:

```
13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
```

It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has
not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

### Marking criteria

The code must be C or C++. Follow best practices of the chosen language. Code must run without
issues on a standard linux system. Any non-standard configuration or library usage must be noted.
Make notes of any restrictions on program usage. Correctness, maintainability, and completeness of
the solution are important. For submission send an archive containing all the relevant files. The
archive should be named: name_surname_collatz_date.tgz.

## Known limitations

### Integer overflow

There is no explicit mention of input number limit in problem description,
so there it is not guaranteed to fit into any finite numeric type. That means
that in theory, infinite (dynamic) numeric type should be used.

Complexity of algorithm is O(n*l), where n is limit and l is (average) sequence
length. But, as l grows extremely slow, for practical analysis complexity
can be observed and "a bit worse than linear".

In case of using 8-byte unsigned type (uint64_t) (maximum value 1.8e+19), first
overflow happens while trying to count sequence length for start number
61162616361 (=6.11e+10). Using 16-byte unsigned type (__uint128_t, extension
offered by both GCC and Clang), it took me 26 minutes to process for limit
1e+11 while running on Intel i7 7-th gen. PC with 8 logical cores. Assuming
usage of more powerful systems (let's limit it as 100x faster than my PC), it
would stake not less than 5 years to process input 1e+18. Taking in count that
it's extremely unlikely to get any overflow of 16-byte unsigned integer during
computations for start number less than 1e+18 (roughly extrapolating 8-byte
case and adding huge margin), that means that practically 16-byte is enough.

Anyway, implementation is using overflow-safe math operations, and so first
occurrence of overflow during computations would result in program termination.
This guarantee that is computations succeeded, output is correct.

Note: search implementation of "program two" (CPU-time optimized) is dependent
on using compiler-specific extensions which are available on GCC and Clang, but
may not be available on others compilers. Despite that still fits into "run
without issues on standard linux system", as GCC and Clang are available on
those, implementation used by "program one" (simplified) can be build without
dependency to any compiler-specific options. In that case, it would use 8-byte
unsigned type.

### pthread

Multi-thread version of program require linkage to pthread library by-default.
CMake variable "USE_MULTITHREADING" should be set to "NO" to avoid this
requirement.

### Smallest number

Under same start number limit, there may be more than one number that has the
same sequence length. Program is looking for and return only the smallest
one above all with the same maximum sequence length. This is due to problem
description require to "find the starting number", not numbers.

### Little endian

"program two" does not have sufficient implementations to be built targeting
systems with big-endian. It is limited only to little-endian.

## Build instructions

Note: compiler MUST support C++17.

The following instructions should be executed at repository root. Binary file
would be found as ```build/collatz_cli```.

As CMake variables definded from CLI are stored in CMake cache, build directory
(```build``` at repository root) should be deleted before swithing to another
build variant.

### Program one (GCC and CLang only)

```bash
    cmake -DBUILD_TYPE=STD -B build && cmake --build build
```

### Program one (any compiler)

```bash
    cmake -DBUILD_TYPE=STD -DUSE_UINT128=NO -B build && cmake --build build
```

### Program two (GCC and CLang only)

```bash
    cmake -B build && cmake --build build
```

### Program two (GCC and CLang only, without linking pthread)

```bash
    cmake -DUSE_MULTITHREADING=NO -B build && cmake --build build
```
