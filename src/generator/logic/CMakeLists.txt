file(GLOB source_files "**.cxx")

add_library(LogicalSolver ${source_files})

target_include_directories(LogicalSolver INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(LogicalSolver PUBLIC Command Sudoku compiler_flags)