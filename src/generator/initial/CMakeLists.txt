set(source_files
  exception.cxx
  get_generator.cxx
  recursive.cxx
)

add_library(InitialBoardGenerator ${source_files})

target_include_directories(InitialBoardGenerator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(InitialBoardGenerator PUBLIC Sudoku compiler_flags)