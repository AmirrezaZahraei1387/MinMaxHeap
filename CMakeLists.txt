cmake_minimum_required(VERSION 3.23)
project(MinMaxHeap)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(MinMaxH)

add_executable(MinMaxHeap main.cpp)

target_link_libraries(MinMaxHeap PUBLIC MinMaxHeapLib)

target_include_directories(MinMaxHeap PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/MinMaxH"
        )