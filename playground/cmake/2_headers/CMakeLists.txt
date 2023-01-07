# Setup
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(hello.out VERSION 1.0)
add_executable(hello.out main.c)

# Include src directory
target_include_directories(hello.out PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
