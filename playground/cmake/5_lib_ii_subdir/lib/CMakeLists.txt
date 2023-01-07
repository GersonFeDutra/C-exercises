# Add a library
add_library(hello.so STATIC hello.c)
target_include_directories(hello.so PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
