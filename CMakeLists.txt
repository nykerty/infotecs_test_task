cmake_minimum_required(VERSION 3.10)
project(myProject)

add_subdirectory(src/LIB)
add_subdirectory(src/Client)
add_subdirectory(src/Server)

set_target_properties(task_lib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

set_target_properties(Client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(Server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
