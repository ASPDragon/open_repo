cmake_minimum_required(VERSION 3.20)
project(HW_7)

set(CMAKE_CXX_STANDARD 20)

find_package(Protobuf REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
link_directories(${PROTOBUF}/lib)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS cmake-build-debug/classes.proto)

set(PROJECT_SRC
        main.cpp
        cmake-build-debug/IRepository.h
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        cmake-build-debug/IMethods.h
        cmake-build-debug/StudentsGroup.cpp
        cmake-build-debug/StudentsGroup.h)

add_executable(HW_7 "${PROJECT_SRC}")

target_link_libraries(HW_7 ${Protobuf_LIBRARIES})