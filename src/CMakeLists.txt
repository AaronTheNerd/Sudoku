cmake_minimum_required(VERSION 3.15)
project(Sudoku VERSION 0.1)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)
target_compile_options(compiler_flags INTERFACE "$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>")

configure_file(config.h.in config.h)

add_executable(Sudoku main.cxx)

target_link_libraries(Sudoku PUBLIC compiler_flags)

target_include_directories(Sudoku PUBLIC "${PROJECT_BINARY_DIR}")
