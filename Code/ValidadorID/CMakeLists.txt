cmake_minimum_required(VERSION 3.16)
project(ValidadorID LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(ValidadorID
    Interfaz.cpp
    Logica.cpp
    Logica.h
)

target_link_libraries(ValidadorID PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
