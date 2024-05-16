file(GLOB source_files "**.cxx")

add_library(Removal ${source_files})

target_include_directories(Removal INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Removal PUBLIC Sudoku compiler_flags)
