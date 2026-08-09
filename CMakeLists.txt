cmake_minimum_required(VERSION 3.14)
project(sk_lang LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(sk)
add_subdirectory(skc)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.8.1
)
FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE ROOT_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cc)
add_executable(sk_lang_tests ${ROOT_TESTS})

target_link_libraries(sk_lang_tests PRIVATE
    sk_lib
    skc_lib
    Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(sk_lang_tests)

