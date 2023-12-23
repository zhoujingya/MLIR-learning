#!/usr/bin/bash

cmake -B build \
    -S . \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug \
    -DLT_LLVM_INSTALL_DIR=$HOME/tools/clang16 \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake --build build