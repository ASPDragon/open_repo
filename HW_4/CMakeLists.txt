cmake_minimum_required(VERSION 3.5)

project(HW4_Complex LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES
    main.cpp
    Insert_sorted.hpp
    DigitalSignalErr.hpp
)

add_executable(HW4_Complex "${SOURCES}")
