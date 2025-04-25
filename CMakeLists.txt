cmake_minimum_required(VERSION 3.10)
project(RingBuffer VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# 添加测试可执行文件
add_executable(ring_buffer_test tests/ring_buffer_test.cpp)
