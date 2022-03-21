cmake_minimum_required(VERSION 3.21)

project("maroontress-lighter")

set(CMAKE_CXX_STANDARD 23)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

include_directories(include)

include(CTest)

add_subdirectory("examples")
add_subdirectory("testsuites")
