cmake_minimum_required(VERSION 3.5)

project(lox-compiler-suite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
# compiler options
add_compile_options(-g -Wall -fPIC)
# lots of warnings and errors.
add_compile_options(-Wall -Wextra -pedantic -Werror)

include_directories("${PROJECT_SOURCE_DIR}/include")
add_subdirectory("${PROJECT_SOURCE_DIR}/src")

# build the test executable
find_package(doctest REQUIRED)

# Make test executable
add_executable(test tests/main.cpp src/lexer.cpp src/debug.cpp src/interpreter.cpp src/tokens.cpp
  src/types.cpp src/ast.cpp)
target_compile_features(test PRIVATE cxx_std_17)
target_link_libraries(test PRIVATE doctest::doctest)# build the main executable

# build the binary
add_executable(lox src/main.cpp src/lexer.cpp src/debug.cpp src/interpreter.cpp src/tokens.cpp
  src/types.cpp src/ast.cpp)
target_include_directories(lox PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(lox liblox)

target_link_libraries(liblox ${extra_libs})

# setup clang-tidy
# clang-tidy
if (NOT DEFINED CLANG_TIDY_BIN)
    # attempt to find the binary if user did not specify
    find_program(CLANG_TIDY_BIN
            NAMES clang-tidy clang-tidy-12)
endif()
if ("${CLANG_TIDY_BIN}" STREQUAL "CLANG_TIDY_BIN-NOTFOUND")
    message(WARNING "lox/main couldn't find clang-tidy.")
else()
    # Output compile_commands.json
    set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
    message(STATUS "lox/main found clang-tidy at ${CLANG_TIDY_BIN}")
endif()
