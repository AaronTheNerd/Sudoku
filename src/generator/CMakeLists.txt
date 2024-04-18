file(GLOB source_files "**.cxx")

add_library(SudokuGenerator ${source_files})

add_subdirectory(initial)

target_include_directories(SudokuGenerator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(SudokuGenerator PUBLIC Sudoku InitialBoardGenerator compiler_flags)