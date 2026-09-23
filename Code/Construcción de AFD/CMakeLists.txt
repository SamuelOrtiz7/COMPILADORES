cmake_minimum_required(VERSION 3.16)
project(afd_qt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(afd_qt
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    afd.h
    afd.cpp
)

target_link_libraries(afd_qt PRIVATE Qt6::Widgets)
