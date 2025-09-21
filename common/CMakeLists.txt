cmake_minimum_required(VERSION 3.5)
project(common LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Network)
add_library(common STATIC
    NetworkManager.cpp
    NetworkManager.h
)

target_link_libraries(common
    Qt5::Core
    Qt5::Network
)
