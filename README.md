# Sudoku
========

Run `ctest -T Test -T Coverage` within `build/` directory to run unit tests and view general coverage report.

Run `bash coverage/coverage.sh` within `Sudoku/` directory to create a clean build, run all unit tests, and generate `gcovr` and `lcov` coverage reports.

Run `find . -iname '*.h' -o -iname '*.cxx' | xargs clang-format -i` within `main/` directory to format all source code files

https://www.sudokuoftheday.com/difficulty