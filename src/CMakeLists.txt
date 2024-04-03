cmake_minimum_required(VERSION 3.15)
project(SudokuGenerator VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(compiler_flags INTERFACE)
target_compile_options(compiler_flags INTERFACE "$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>")

configure_file(config.h.in config.h)

add_subdirectory(sudoku)



add_executable(main main.cxx)
target_include_directories(main INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(main PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(main PUBLIC compiler_flags Sudoku)



include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB test_files "test/**.cxx")
add_executable(sudoku_test ${test_files})
target_include_directories(sudoku_test INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sudoku_test PUBLIC compiler_flags Sudoku GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(sudoku_test)
