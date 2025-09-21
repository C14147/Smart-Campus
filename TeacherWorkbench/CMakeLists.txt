cmake_minimum_required(VERSION 3.16)
project(TeacherWorkbench LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Network Gui Widgets)
add_executable(TeacherWorkbench
    ../common/NetworkManager.cpp
    ../common/NetworkManager.h
)

target_link_libraries(TeacherWorkbench
    Qt5::Core
    Qt5::Network
    Qt5::Gui
    Qt5::Widgets
    common # internal shared library, if exists
)
target_include_directories(TeacherWorkbench PRIVATE ../common)
