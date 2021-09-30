cmake_minimum_required(VERSION 3.20)

project(HW_1 VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_SOURCES
    src/libs/Person.hpp
    src/libs/Person.cpp
    src/libs/PhoneNumber.hpp
    src/libs/PhoneNumber.cpp
    src/libs/PhoneBook.hpp
    src/libs/PhoneBook.cpp
    src/main.cpp
)

add_executable(HW_1 "${PROJECT_SOURCES}")