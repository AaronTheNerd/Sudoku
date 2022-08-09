// Written by Aaron Barge
// Copyright 2022

#include <chrono>
#include <iostream>
#include <stdexcept>

#define TEST_SUITE_INIT()                                              \
  auto __tests_start__    = std::chrono::high_resolution_clock::now(); \
  size_t __tests_run__    = 0;                                         \
  size_t __tests_failed__ = 0;

#define TEST_INIT() size_t __test_num__ = 1;

#define ASSERT(x)                                               \
  if (!(x)) {                                                   \
    throw std::runtime_error("Assertion failed!\n" __FILE__ ":" \
        + std::to_string(__LINE__) + ":\n  ASSERT(" #x ")");    \
  }

#define TEST_CASE(print_name)                                                \
  std::cout << "Running test #" << __test_num__ << ": " << (print_name)      \
            << std::endl;                                                    \
  std::cout << "---------------------------------------------" << std::endl; \
  __test_num__++;

#define TEST_SUITE(print_name, code)                                         \
  {                                                                          \
    auto start = std::chrono::high_resolution_clock::now();                  \
    try {                                                                    \
      std::cout << "\n\n\nRunning Test Suite " << (print_name) << std::endl; \
      std::cout << "============================================="           \
                << std::endl;                                                \
      __tests_run__++;                                                       \
      code;                                                                  \
    } catch (const std::runtime_error& error) {                              \
      std::cerr << error.what() << std::endl;                                \
      __tests_failed__++;                                                    \
    }                                                                        \
    auto end = std::chrono::high_resolution_clock::now();                    \
    std::chrono::duration<double, std::milli> duration = end - start;        \
    std::cout << "Completed in " << duration.count() << "ms" << std::endl;   \
  }

#define PRINT_RESULTS()                                                        \
  auto __tests_end__ = std::chrono::high_resolution_clock::now();              \
  std::chrono::duration<double, std::milli> duration =                         \
      __tests_end__ - __tests_start__;                                         \
  std::cout << std::endl << std::endl << std::endl << "RESULTS:" << std::endl; \
  std::cout << "=============================================" << std::endl;   \
  std::cout << "Test Suites Completed after " << duration.count() << "ms"      \
            << std::endl;                                                      \
  std::cout << (__tests_run__ - __tests_failed__) << "/" << (__tests_run__)    \
            << " Test Suites Finished Successfully" << std::endl;
