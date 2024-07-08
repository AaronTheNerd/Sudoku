# Sudoku
========

Run `ctest -T Test -T Coverage` within `build/` directory to run unit tests and view coverage report.

Run `gcovr --root .. --filter ../src/ --exclude ../src/test/ --exclude ../src/main.cxx --html coverage.html` within `build/` directory to generate a `coverage.html` report.

Run `find . -iname '*.h' -o -iname '*.cxx' | xargs clang-format -i` within `main/` directory to format all source code files

https://www.sudokuoftheday.com/difficulty