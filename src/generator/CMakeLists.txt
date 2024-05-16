file(GLOB source_files "**.cxx")

add_library(SudokuGenerator ${source_files})

add_subdirectory(initial)
add_subdirectory(removal)
add_subdirectory(command)
add_subdirectory(logic)

target_include_directories(SudokuGenerator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(SudokuGenerator PUBLIC Sudoku InitialBoardGenerator Removal Command LogicalSolver compiler_flags)