CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)

PROJECT(AllocatorTest)

add_library(Alloc STATIC Allocator/allocator.cc  Allocator/allocator.h  Allocator/linearallocator.cc Allocator/linearallocator.h)

ADD_EXECUTABLE(AllocatorTest main.cc)
target_link_libraries(AllocatorTest PUBLIC Alloc)