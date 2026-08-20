#!/usr/bin/env bash
# Compila (y opcionalmente ejecuta) el proyecto AL con CMake, con un solo comando.
# Uso:
#   ./build.sh        -> compila (genera ./build y el binario ./build/AL)
#   ./build.sh run     -> compila y ejecuta ./build/AL al terminar
set -e

cd "$(dirname "$0")"

if ! command -v cmake &> /dev/null; then
    echo "No se encontro cmake en el PATH."
    echo "Instala las dependencias con:"
    echo "  sudo apt install cmake qtbase5-dev qt5-qmake"
    exit 1
fi

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j"$(nproc)"

if [ "$1" == "run" ]; then
    ./build/AL
fi
