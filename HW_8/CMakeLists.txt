cmake_minimum_required(VERSION 3.20)
project(HW_8)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

set(PROJECT_SRC
        cmake-build-debug/Person.hpp
        cmake-build-debug/Person.cpp
        cmake-build-debug/PhoneNumber.hpp
        cmake-build-debug/PhoneNumber.cpp
        cmake-build-debug/PhoneBook.hpp
        cmake-build-debug/PhoneBook.cpp
        main.cpp
        cmake-build-debug/Tests.hpp)

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

target_link_libraries(${PROJECT_NAME}
        GTest::gtest GTest::gtest_main
        )

enable_testing()
