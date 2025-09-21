cmake_minimum_required(VERSION 3.5)
project(RoomFunctionDisplay LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Network Gui Widgets)
add_executable(RoomFunctionDisplay
    ../common/NetworkManager.cpp
    ../common/NetworkManager.h
)

target_link_libraries(RoomFunctionDisplay
    Qt5::Core
    Qt5::Network
    Qt5::Gui
    Qt5::Widgets
    common
)
target_include_directories(RoomFunctionDisplay PRIVATE ../common)
