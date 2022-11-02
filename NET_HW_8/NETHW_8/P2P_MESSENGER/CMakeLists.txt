cmake_minimum_required(VERSION 3.23)

project(P2P_MESSENGER)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_SOURCES main.cpp Peer.hpp Peer.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})