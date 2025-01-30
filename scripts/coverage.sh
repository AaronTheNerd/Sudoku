dir="$(cd -P -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)"
cd $dir/../build
cmake --build . --target clean
cmake --build . --target all
lcov -c -i --ignore-errors mismatch -d .. -o base.info
./test/sudoku_test
lcov -c --ignore-errors mismatch -d .. -o test.info
lcov -a base.info -a test.info -o total.info
lcov --remove total.info -o filtered.info '/usr/*' '*build/_deps*' '*src/test/*' '*src/main.cxx'
genhtml filtered.info -o ../scripts/output
gcovr --root .. --filter ../src/ --exclude ../src/test/ --exclude ../src/main.cxx --html ../scripts/output/gcovr.html --html-theme github.dark-green
google-chrome ../scripts/output/gcovr.html
google-chrome ../scripts/output/index.html
