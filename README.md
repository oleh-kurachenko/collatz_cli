# collatz_cli

CLI tool for searching number m in range 1..n, so there lenght of Collatz
sequence is the biggest among others. This is a test task. Generally, I'm
quite sceptical about doing test tasks during job search, but Collatz problem
is my old love, so here it is.

## Known limitations

There is no explicit mention of input number limit in problem description,
so there it is not guaranteed to fit into any finite numeric type. But, let's
try to estimate what happens if we take 8-byte unsigned integer to store
our calculations.

The starting number having the largest sequence length while being less than
10e+12 is 989345275647, sequence length is 1348. Max element of that sequence
is 1219624271099764, which is less than 1e+16. On that basis, we may assume
that it is likely that no other element of sequences with starting number
less than 10e+12 reach this (1e+16) limit.
10e+9 trivial (O(1)) operations takes roughly 1 second of execution.
Complexity of algorithm is O(n * l), where l is (average) sequence length.
For n ~= 10e+12, average sequence length (l) is ~= 300, so while running for 
at least 70 hours, we are expecting to operate with numbers which are less than
10e+16.

For this reason, for the sake of not searching/writing infinite numeric type
implementation, I'm going to use 8-byte unsigned integer type to store
computation values. I'm also going to watch for overflow, to be able to
catch threshold where program no longer able to produce correct output.

## Notes

TODO: add proof for ```if (t_next < t)```

Looking only for the first one?
