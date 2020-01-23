set(SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/Lexer.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Lexer.cpp"
)

add_subdirectory(lexerTests)
get_directory_property(
  SOURCES_lexerTests DIRECTORY lexerTests DEFINITION SOURCES
)