cmake_minimum_required(VERSION 3.16)
project(AL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Genera build/compile_commands.json para que IntelliSense (VS Code)
# encuentre los headers de Qt automaticamente, sin configurarlos a mano.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Necesario para que moc procese los Q_OBJECT de MainWindow.h
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Busca Qt6 primero y, si no esta, cae a Qt5. Ambos sirven para este proyecto.
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(AL
    interfaz/Main.cpp
    interfaz/MainWindow.cpp
    interfaz/MainWindow.h
    code/Punto1Estructuras.cpp
    code/Punto1Estructuras.h
    code/Punto2Alfabeto.cpp
    code/Punto2Alfabeto.h
    code/Punto3Regex.cpp
    code/Punto3Regex.h
)

target_include_directories(AL PRIVATE code interfaz)
target_link_libraries(AL PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
