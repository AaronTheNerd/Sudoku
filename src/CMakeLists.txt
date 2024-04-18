cmake_minimum_required(VERSION 3.15)
project(SudokuGenerator VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(compiler_flags INTERFACE)
target_compile_options(compiler_flags INTERFACE "$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused;-O3>")

configure_file(config.h.in config.h)

add_subdirectory(sudoku)
add_subdirectory(generator)

add_executable(main main.cxx)
target_include_directories(main INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(main PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(main PUBLIC compiler_flags Sudoku SudokuGenerator)

add_subdirectory(test)
