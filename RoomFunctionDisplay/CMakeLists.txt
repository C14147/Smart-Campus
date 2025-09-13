cmake_minimum_required(VERSION 3.16)
project(RoomFunctionDisplay LANGUAGES CXX)
    # Platform adaptation: Only build on Android
    if(NOT ANDROID)
        message(FATAL_ERROR "RoomFunctionDisplay is only supported on Android platform.")
    endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network Gui Widgets)
add_executable(RoomFunctionDisplay
    main.cpp
    # ... other source files ...
    ../common/NetworkManager.cpp
    ../common/NetworkManager.h
)

target_link_libraries(RoomFunctionDisplay
    Qt6::Core
    Qt6::Network
    Qt6::Gui
    Qt6::Widgets
    common
)
target_include_directories(RoomFunctionDisplay PRIVATE ../common)
