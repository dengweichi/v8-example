cmake_minimum_required(VERSION 3.16)
project(v8_example)

set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR}/include/v8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pthread -DV8_COMPRESS_POINTERS")
add_executable(v8_example main.cpp)
target_link_libraries(v8_example ${PROJECT_SOURCE_DIR}/deps/v8/libv8_monolith.a ${PROJECT_SOURCE_DIR}/deps/v8/libv8_libplatform.a ${PROJECT_SOURCE_DIR}/deps/v8/libv8_libbase.a)