cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(AllocatorTest)

add_subdirectory(Allocator)
add_executable(AllocatorTest main.cc)
target_link_libraries(AllocatorTest PUBLIC Allocator)