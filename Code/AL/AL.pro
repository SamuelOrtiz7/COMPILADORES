QT       += core gui widgets

CONFIG   += c++17
TEMPLATE = app
TARGET   = AL

INCLUDEPATH += code interfaz

SOURCES += \
    interfaz/Main.cpp \
    interfaz/MainWindow.cpp \
    code/Punto1Estructuras.cpp \
    code/Punto2Alfabeto.cpp \
    code/Punto3Regex.cpp

HEADERS += \
    interfaz/MainWindow.h \
    code/Punto1Estructuras.h \
    code/Punto2Alfabeto.h \
    code/Punto3Regex.h
