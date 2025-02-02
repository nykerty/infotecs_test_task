cmake_minimum_required(VERSION 3.10)
project(Server)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/task_lib)

add_executable(Server main.cpp server.cpp)
target_link_libraries(Server task_lib)
