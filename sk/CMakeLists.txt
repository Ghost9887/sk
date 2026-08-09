cmake_minimum_required(VERSION 3.10)
project(sk)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

file(GLOB_RECURSE APP_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cc
)

add_executable(sk ${APP_SOURCES})

target_include_directories(sk
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_compile_options(sk PRIVATE -Wall -Wextra -Wpedantic)
