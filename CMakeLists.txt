cmake_minimum_required(VERSION 3.10)

# Set the project name
project(bucketSort)
set(CMAKE_CXX_STANDARD 17)

add_executable(bucketSort src/test.cpp src/bucketSort.cpp src/catch.cpp )