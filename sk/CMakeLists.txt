file(GLOB_RECURSE SK_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
)

list(REMOVE_ITEM SK_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc
)

add_library(sk_lib ${SK_SOURCES})

target_include_directories(sk_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(sk_lib PRIVATE -Wall -Wextra -Wpedantic -Og -g)

add_executable(sk ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc)
target_link_libraries(sk PRIVATE sk_lib)
