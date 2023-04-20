cmake_minimum_required(VERSION 3.22)
project(algorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_BINARY_DIR ./build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

add_subdirectory(src)
add_subdirectory(tests)
