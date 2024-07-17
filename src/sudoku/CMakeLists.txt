set(source_files
  board.cxx
  cell.cxx
  index.cxx
  options.cxx
  position.cxx
  validate.cxx
  value.cxx
)

add_library(Sudoku ${source_files})

target_include_directories(Sudoku INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Sudoku PUBLIC compiler_flags)
