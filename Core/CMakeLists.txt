cmake_minimum_required(VERSION 3.16)
project(CampusCore LANGUAGES CXX)

# Platform adaptation: Only build on Windows or Linux
if(NOT (WIN32 OR UNIX))
    message(FATAL_ERROR "CampusCore is only supported on Windows and Linux platforms.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network)
add_executable(CampusCore
    main.cpp
    CampusCoreServer.cpp
    CampusCoreServer.h
)

target_link_libraries(CampusCore
    Qt6::Core
    Qt6::Network
    common # internal shared library, if exists
)
target_include_directories(CampusCore PRIVATE ../common)
