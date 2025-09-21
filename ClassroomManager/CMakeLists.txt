cmake_minimum_required(VERSION 3.5)
project(ClassroomManager LANGUAGES CXX)

# Platform adaptation: Only build on Windows or Android
if(NOT (WIN32 OR ANDROID))
    message(FATAL_ERROR "ClassroomManager is only supported on Windows and Android platforms.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Network Gui Widgets)
add_executable(ClassroomManager
    ../common/NetworkManager.cpp
    ../common/NetworkManager.h
)

target_link_libraries(ClassroomManager
    Qt5::Core
    Qt5::Network
    Qt5::Gui
    Qt5::Widgets
    common
)
target_include_directories(ClassroomManager PRIVATE ../common)
