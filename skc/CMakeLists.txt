cmake_minimum_required(VERSION 3.14)
project(skc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE APP_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cc)

list(REMOVE_ITEM APP_SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cc
)

add_library(skc_lib ${APP_SOURCES})
target_include_directories(skc_lib PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_compile_options(skc_lib PRIVATE -Wall -Wextra -Wpedantic -Og -g)

add_executable(skc ${CMAKE_SOURCE_DIR}/src/main.cc)
target_link_libraries(skc PRIVATE skc_lib)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/*.cc)
add_executable(skc_tests ${TEST_SOURCES})
target_link_libraries(skc_tests PRIVATE 
    skc_lib
    Catch2::Catch2WithMain
)
