#!/bin/bash
set -e

# # Deleta a pasta build se existir
# rm -rf build

# Cria novamente
mkdir -p build
cd build

# Gera arquivos de build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

MAX_THREADS=12
THREADS=$(nproc)
if [ "$THREADS" -gt "$MAX_THREADS" ]; then
    THREADS=$MAX_THREADS
fi

make -j$THREADS


# Limpa a tela
clear

# Executa o programa
make run
