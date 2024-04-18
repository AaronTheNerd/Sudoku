include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB source_files "**.cxx")

add_executable(sudoku_test ${source_files})
target_include_directories(main PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(sudoku_test PUBLIC compiler_flags Sudoku SudokuGenerator GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(sudoku_test)
