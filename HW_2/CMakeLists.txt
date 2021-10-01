cmake_minimum_required(VERSION 3.20)

project(HW_2 VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_SOURCES
    src/libs/TemplateFuncs.hpp
    src/libs/Timer.hpp
    src/libs/VowelCounter.hpp
    src/libs/VowelCounter.cpp
    src/main.cpp
)

add_executable(HW_2 "${PROJECT_SOURCES}")