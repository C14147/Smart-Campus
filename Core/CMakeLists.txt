cmake_minimum_required(VERSION 3.5)
project(CampusCore LANGUAGES CXX)

# Platform adaptation: Only build on Windows or Linux
if(NOT (WIN32 OR UNIX))
    message(FATAL_ERROR "CampusCore is only supported on Windows and Linux platforms.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Network)
add_executable(CampusCore
    CampusCoreServer.cpp
    CampusCoreServer.h
)

target_link_libraries(CampusCore
    Qt5::Core
    Qt5::Network
    common # internal shared library, if exists
)
target_include_directories(CampusCore PRIVATE ../common)
