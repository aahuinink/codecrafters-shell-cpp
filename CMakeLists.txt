cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard

set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)

project(myshell)

add_executable(shell src/main.cpp)

add_subdirectory(lib_repl)

target_link_libraries(shell PRIVATE repl)
