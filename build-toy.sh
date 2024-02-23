#!/usr/bin/bash

LLVM_TOOL_PATH=$HOME/tools/clang17
export PATH=$LLVM_TOOL_PATH/bin:$PATH

# Building toy dialec

cmake -B build_toy \
    -S . \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug \
    -DLT_LLVM_INSTALL_DIR=$LLVM_TOOL_PATH\
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DLLVM_VERSION_=17 \
    -DCMAKE_BUILD_TYPE=Debug


cmake --build build_toy