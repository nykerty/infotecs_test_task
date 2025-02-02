cmake_minimum_required(VERSION 3.10)
project(task_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(task_lib SHARED task_lib.cpp)

target_include_directories(task_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(task_lib PRIVATE TASKLIB_EXPORTS)