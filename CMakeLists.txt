cmake_minimum_required(VERSION 3.10)
project(sk LANGUAGES CXX)

file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cc
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sk ${SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/include)

target_compile_options(sk PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
