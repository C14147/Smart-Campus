cmake_minimum_required(VERSION 3.16)
project(common LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

add_library(common STATIC
    NetworkManager.cpp
    NetworkManager.h
)

target_link_libraries(common
    Qt6::Core
    Qt6::Network
)
