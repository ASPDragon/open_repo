cmake_minimum_required(VERSION 3.20)

project(HW_3 )

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_SOURCES
    src/libs/Iterator.hpp
    src/libs/Matrix.hpp
    src/libs/Matrix.cpp
    src/libs/Templates.hpp
    src/libs/ArrayInt.hpp
    src/main.cpp
)

add_executable(HW_3 "${PROJECT_SOURCES}")
