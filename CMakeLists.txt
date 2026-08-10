cmake_minimum_required(VERSION 3.19)

project(sk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
)

FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE APP_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
)

list(REMOVE_ITEM APP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc
)

add_library(sk_lib ${APP_SOURCES})

target_include_directories(sk_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(sk_lib PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

add_executable(sk
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc
)

target_link_libraries(sk PRIVATE
    sk_lib
)

file(GLOB_RECURSE ROOT_TESTS
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cc
)

add_executable(sk_tests ${ROOT_TESTS})

target_link_libraries(sk_tests PRIVATE
    sk_lib
    Catch2::Catch2WithMain
)

include(CTest)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(sk_tests)
