@echo off
REM Compila (y opcionalmente ejecuta) el proyecto AL con CMake, con un solo comando.
REM Uso:
REM   build.bat         -> compila (genera .\build y build\AL.exe)
REM   build.bat run      -> compila y ejecuta build\AL.exe al terminar
REM
REM Requiere cmake y un generador (MinGW Makefiles o Ninja) en el PATH.

where cmake >nul 2>nul
if errorlevel 1 (
    echo No se encontro cmake en el PATH.
    exit /b 1
)

cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
if errorlevel 1 exit /b 1

cmake --build build
if errorlevel 1 exit /b 1

if "%1"=="run" (
    build\AL.exe
)
