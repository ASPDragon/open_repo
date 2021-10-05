cmake_minimum_required(VERSION 3.20)

project(HW4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES
    main.cpp
    Insert_sorted.hpp
    DigitalSignalErr.hpp
)

add_executable(HW4 "${SOURCES}")
