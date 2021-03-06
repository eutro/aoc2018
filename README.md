# AOC 2018

Solutions to [Advent of Code 2018](https://adventofcode.com/2018) written in C++.

# Building

Executables can be built with [cmake](https://cmake.org/).
There is one executable for each day, named `dayXX` for day `XX`.

This is an example of how to build:
```sh
mkdir build && cd build
cmake ..
cmake --build .
```

And to execute:
```sh
./dayXX < ../input/dayXX.txt
```
