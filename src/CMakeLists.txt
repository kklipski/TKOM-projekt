cmake_minimum_required(VERSION 3.10)
 
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

project(TKOM-2020 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

include_directories("${CMAKE_SOURCE_DIR}")

set(SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/commonElements.h"
)

add_subdirectory(ast)
get_directory_property(
  SOURCES_ast DIRECTORY ast DEFINITION SOURCES
)
add_subdirectory(lexer)
get_directory_property(
  SOURCES_lexer DIRECTORY lexer DEFINITION SOURCES
)
add_subdirectory(parser)
get_directory_property(
  SOURCES_parser DIRECTORY parser DEFINITION SOURCES
)

add_executable(interpreter.out
  interpreter.cpp
  "${SOURCES}"
  "${SOURCES_ast}"
  "${SOURCES_lexer}"
  "${SOURCES_parser}"
)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to the build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Link against gtest_main
add_executable(lexerTests.out
  lexer/lexerTests/test.cpp
  "${SOURCES_lexer}"
  "${SOURCES_lexerTests}"
)

add_executable(parserTests.out
  parser/parserTests/test.cpp
  "${SOURCES}"
  "${SOURCES_ast}"
  "${SOURCES_lexer}"
  "${SOURCES_parser}"
  "${SOURCES_parserTests}"
)

add_executable(astTests.out
  ast/astTests/test.cpp
  "${SOURCES}"
  "${SOURCES_ast}"
  "${SOURCES_lexer}"
  "${SOURCES_parser}"
  "${SOURCES_astTests}"
)

target_link_libraries(lexerTests.out gtest_main)
target_link_libraries(parserTests.out gtest_main)
target_link_libraries(astTests.out gtest_main)
add_test(NAME lexerTests.out COMMAND lexerTests.out)
add_test(NAME parserTests.out COMMAND parserTests.out)
add_test(NAME astTests.out COMMAND astTests.out)