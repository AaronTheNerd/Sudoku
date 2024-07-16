# Sudoku

A sudoku puzzle generator written in C++20.

## Build

In the top-level directory run:
```
$ mkdir build
$ cd build/
$ cmake ../src/
```
to configure cmake.

In the `build/` directory you can now run:
```
cmake --build .
```
to build the program.

## Coverage Reports

Run `ctest -T Test -T Coverage` within `build/` directory to run unit tests and view general coverage report.

Run `bash coverage/coverage.sh` within `Sudoku/` directory to create a clean build, run all unit tests, and generate `gcovr` and `lcov` coverage reports.

## Formatting

Run `find . -iname '*.h' -o -iname '*.cxx' | xargs clang-format -i` within `main/` directory to format all source code files

# Next Steps

- Replace technique classes with functions


# Resources

https://www.sudokuoftheday.com/difficulty