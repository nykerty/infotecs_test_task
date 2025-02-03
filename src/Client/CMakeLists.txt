cmake_minimum_required(VERSION 3.10)
project(Client)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/task_lib)

add_executable(Client main.cpp client.cpp)

target_link_libraries(Client PRIVATE task_lib)

target_include_directories(Client PRIVATE ${CMAKE_SOURCE_DIR}/LIB)
