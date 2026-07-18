#!/bin/bash
set -e

# 1. Define o Clang como compilador padrão para este build
export CC=clang
export CXX=clang++

# Deleta a pasta build se existir para garantir um build limpo
rm -rf build

# Cria e entra na pasta build usando uma subshell para evitar desalinhamento de diretório
mkdir -p build
cd build

# 2. Gera arquivos de build (com Clang e comandos de compilação para o LSP)
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

# 3. Descobre o número de threads limitando a 12
MAX_THREADS=12
THREADS=$(nproc)
if [ "$THREADS" -gt "$MAX_THREADS" ]; then
    THREADS=$MAX_THREADS
fi

# 4. Compila usando o CMake de forma agnóstica (melhor que chamar 'make' direto)
cmake --build . -j $THREADS

# Copia o compile_commands.json para a raiz (ajuda muito o Clangd/LSP a achar os includes da ICU)
cp compile_commands.json ..

# Limpa a tela
clear

# 5. Executa o programa com segurança
# Se você tiver "add_custom_target(run ...)" no CMake:
if make -q run 2>/dev/null; then
    make run
else
    # Caso contrário, executa o binário direto (ajuste 'meu_programa' para o nome do seu executável)
    ./ayla 
fi
