#!/bin/bash

# Пути к инструментам (используем Windows-стиль путей)
export CC="C:/msys64/mingw64/bin/gcc.exe"
export CXX="C:/msys64/mingw64/bin/g++.exe"
export CMAKE="C:/msys64/mingw64/bin/cmake.exe"
export NINJA="C:/msys64/mingw64/bin/ninja.exe"

# Проверка наличия необходимых программ
for tool in "$CC" "$CXX" "$CMAKE" "$NINJA"; do
    if [ ! -f "$tool" ]; then
        echo "❌ Ошибка: не найден $tool"
        echo "Проверьте установку MSYS2 и пакетов:"
        echo "pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja"
        exit 1
    fi
done

# Генератор (Ninja или MinGW Makefiles)
GENERATOR="Ninja"

# Директория сборки
BUILD_DIR="build"

echo "=== Запуск CMake ==="
"$CMAKE" -S . -B "$BUILD_DIR" -G "$GENERATOR" \
    -DCMAKE_C_COMPILER="$CC" \
    -DCMAKE_CXX_COMPILER="$CXX" \
    -DCMAKE_MAKE_PROGRAM="$NINJA"

if [ $? -ne 0 ]; then
    echo "❌ Ошибка CMake!"
    exit 1
fi

echo "=== Сборка проекта ==="
"$CMAKE" --build "$BUILD_DIR" --verbose

if [ $? -ne 0 ]; then
    echo "❌ Ошибка сборки!"
    exit 1
fi

echo "✅ Сборка успешно завершена!"