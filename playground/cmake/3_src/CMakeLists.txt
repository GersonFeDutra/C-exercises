# Setup
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(hello.out VERSION 1.0)

# Traditional way of adding multiple sources
# add_executable(hello.out src/hello.c src/world.c main.c)

# Add multiple sources recursively
# CMake descourage this. See: <https://cmake.org/cmake/help/latest/command/file.html#filesystem>
file(GLOB_RECURSE SRC_FILES src/*.c)
add_executable(hello.out ${SRC_FILES} main.c)

# Include src directory
target_include_directories(hello.out PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
