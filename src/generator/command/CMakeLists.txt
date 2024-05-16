file(GLOB source_files "**.cxx")

add_library(Command ${source_files})

target_include_directories(Command INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Command PUBLIC Sudoku compiler_flags)