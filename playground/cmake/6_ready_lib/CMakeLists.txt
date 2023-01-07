# Setup
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(hello.out VERSION 1.0)

# External Package: SFML
# Install the library in your system. Ex.: yay -S sfml
find_package(SFML 2 REQUIRED network audio graphics window system)
# Build fail if it can't find it
# This sets some 'result' variables ( _INCLUDE_DIRS(S), _LIBRARIES, etc).
# although can differ from library to library

# Add subdirectory library
add_subdirectory(lib)

# Traditional way of adding multiple sources
# add_executable(hello.out src/hello.c src/world.c main.c)

# Add multiple sources recursively
# CMake descourage this. See: <https://cmake.org/cmake/help/latest/command/file.html#filesystem>
file(GLOB_RECURSE SRC_FILES src/*.c)
add_executable(hello.out ${SRC_FILES} main.cpp)

# Include the package
target_include_directories(hello.out PUBLIC ${SFML_INCLUDE_DIR})

# Include src directory
target_include_directories(hello.out PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Link the library, package and dependencies
target_link_libraries(hello.out PUBLIC hello.so ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
