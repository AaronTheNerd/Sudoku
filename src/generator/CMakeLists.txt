set(source_files
  generator.cxx
)

add_library(SudokuGenerator ${source_files})

add_subdirectory(initial)
add_subdirectory(command)
add_subdirectory(logic)

target_include_directories(SudokuGenerator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(SudokuGenerator PUBLIC Sudoku InitialBoardGenerator Command LogicalSolver compiler_flags)