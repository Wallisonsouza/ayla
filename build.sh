#!/bin/bash
set -e

export CC=clang
export CXX=clang++

#  rm -rf build

 mkdir -p build
cd build

# Gera build usando Ninja
cmake -G Ninja \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
..

MAX_THREADS=4
THREADS=$(nproc)

if [ "$THREADS" -gt "$MAX_THREADS" ]; then
    THREADS=$MAX_THREADS
fi

# Compila usando Ninja
ninja -j $THREADS

# Volta para a raiz do projeto
cd ..

ln -sf build/compile_commands.json compile_commands.json

clear

# Executa
cd build

./ayla run ../src/ayla/scripts/io.ayla  --dump ast