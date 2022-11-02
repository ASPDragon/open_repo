cmake_minimum_required(VERSION 3.23)
project(TORRENT_CLIENT)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_SOURCES magnet.cpp client.cpp)

add_executable(magnet "magnet.cpp")
target_link_libraries(magnet PRIVATE torrent-rasterbar)

add_executable(torrent-client "client.cpp")
target_link_libraries(torrent-client PRIVATE torrent-rasterbar)