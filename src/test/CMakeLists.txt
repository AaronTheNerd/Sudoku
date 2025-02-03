include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(source_files
  board_validator.cxx
  board.cxx
  candidate_lines.cxx
  cell.cxx
  cell_group.cxx
  commands.cxx
  difficulty.cxx
  candidate_box.cxx
  generator.cxx
  index.cxx
  initial_board.cxx
  options.cxx
  position.cxx
  single_candidate.cxx
  single_position.cxx
  test_utils.cxx
  value.cxx
  line_box_view.cxx
)

add_executable(sudoku_test ${source_files})
target_include_directories(main PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(sudoku_test PUBLIC compiler_flags Sudoku SudokuGenerator GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(sudoku_test)
