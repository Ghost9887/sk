file(GLOB_RECURSE SKC_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
)

list(REMOVE_ITEM SKC_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc
)

add_library(skc_lib ${SKC_SOURCES})

target_include_directories(skc_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(skc_lib PRIVATE -Wall -Wextra -Wpedantic -Og -g)

add_executable(skc ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc)
target_link_libraries(skc PRIVATE skc_lib)
