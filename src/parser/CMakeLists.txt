set(SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/Parser.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Parser.cpp"
)

add_subdirectory(parserTests)
get_directory_property(
  SOURCES_parserTests DIRECTORY parserTests DEFINITION SOURCES
)