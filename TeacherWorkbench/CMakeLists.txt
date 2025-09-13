cmake_minimum_required(VERSION 3.16)
project(TeacherWorkbench LANGUAGES CXX)

 # Platform adaptation: Only build on Windows, macOS, or Android
 if(NOT (WIN32 OR APPLE OR ANDROID))
     message(FATAL_ERROR "TeacherWorkbench is only supported on Windows, macOS, and Android platforms.")
 endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network Gui Widgets)
add_executable(TeacherWorkbench
    main.cpp
    # ... other source files ...
    ../common/NetworkManager.cpp
    ../common/NetworkManager.h
)

target_link_libraries(TeacherWorkbench
    Qt6::Core
    Qt6::Network
    Qt6::Gui
    Qt6::Widgets
    common # internal shared library, if exists
)
target_include_directories(TeacherWorkbench PRIVATE ../common)
