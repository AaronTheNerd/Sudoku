// Written by Aaron Barge
// Copyright 2022

#include <chrono>
#include <iostream>
#include <stdexcept>

#define ASSERT(x)                                               \
  if (!(x)) {                                                   \
    throw std::runtime_error("Assertion failed!\n" __FILE__ ":" \
        + std::to_string(__LINE__) + ":\n  ASSERT(" #x ")");    \
  }

#define TEST_SUITE(print_name)                                               \
  std::cout << "\n\n\nRunning Test Suite " << (print_name) << std::endl;     \
  std::cout << "=============================================" << std::endl; \
  size_t __test_num__ = 1;

#define TEST_CASE(print_name)                                                \
  std::cout << "Running test #" << __test_num__ << ": " << (print_name)      \
            << std::endl;                                                    \
  std::cout << "---------------------------------------------" << std::endl; \
  __test_num__++;

#define TIME(code)                                                         \
  {                                                                        \
    auto start = std::chrono::high_resolution_clock::now();                \
    try {                                                                  \
      code;                                                                \
    } catch (const std::runtime_error& error) {                            \
      std::cerr << error.what() << std::endl;                              \
    }                                                                      \
    auto end = std::chrono::high_resolution_clock::now();                  \
    std::chrono::duration<double, std::milli> duration = end - start;      \
    std::cout << "Completed in " << duration.count() << "ms" << std::endl; \
  }
