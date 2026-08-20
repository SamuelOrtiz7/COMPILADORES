@echo off
REM Compila el proyecto y genera una carpeta portable "dist" con AL.exe
REM y todas las DLLs de Qt necesarias, lista para copiar a cualquier PC
REM con Windows SIN tener Qt instalado.
REM
REM Requisito: correr esto en un PC Windows que SI tenga Qt + MinGW
REM instalados (por ejemplo via Qt Online Installer), con la carpeta
REM bin de Qt en el PATH, ej:  C:\Qt\6.7.0\mingw_64\bin
REM
REM Uso:
REM   deploy-windows.bat

where cmake >nul 2>nul
if errorlevel 1 (
    echo No se encontro cmake en el PATH.
    exit /b 1
)

where windeployqt >nul 2>nul
if errorlevel 1 (
    echo No se encontro windeployqt en el PATH.
    echo Agrega la carpeta bin de Qt al PATH, ej: C:\Qt\6.7.0\mingw_64\bin
    exit /b 1
)

cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
if errorlevel 1 exit /b 1

cmake --build build -j
if errorlevel 1 exit /b 1

if exist dist rmdir /s /q dist
mkdir dist
copy build\AL.exe dist\ >nul

windeployqt --release --compiler-runtime dist\AL.exe
if errorlevel 1 exit /b 1

echo.
echo Listo. La carpeta "dist" es portable.
echo Comprimela en .zip y enviasela a tu profesor: no necesita instalar Qt.
