file(GLOB source_files "**.cxx")

add_library(Sudoku ${source_files})

target_include_directories(Sudoku INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Sudoku PUBLIC compiler_flags)
