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

Run `bash coverage.sh` within `scripts/` directory to create a clean build, run all unit tests, and generate `gcovr` and `lcov` coverage reports.

## Formatting

Run `find . -iname '*.h' -o -iname '*.cxx' | xargs clang-format -i` within `src/` directory to format all source code files

# Next Steps

- Replace technique classes with functions?


# Resources

## Sudoku of the Day

A majority of the decisions for the different difficulty ranges logical techniques to include are from the [Sudoku of the Day website](https://www.sudokuoftheday.com).

While using this resource is a good starting point for this project, I am planning to modify/replace some of the logical techniques used and adjust the difficulty ranges if necessary. 

For example, Sudoku of the Day defines two logical techniques named [double pairs](https://www.sudokuoftheday.com/techniques/double-pairs), and [multiple lines](https://www.sudokuoftheday.com/techniques/multiple-lines). 

These techniques rely on finding a candidate value in two boxes which lie exclusively in two lines in order to remove that candidate from those lines which are not in those two boxes. 

This is not something I've ever searched for when attempting to solve sudoku puzzles. Rather, I take an inverse approach. 

I look for a candidate value in a line and check if they are only in one box. If so, then I can safely remove all of those candidates in that box which are not on that line.

My technique which I have called candidate box encompasses both double pairs and multiple lines while being far easier to spot in my opinion. To ensure that my technique truly can act as either double pairs or multiple lines, I have added the examples from both of those techniques into the test cases for candidate box.
