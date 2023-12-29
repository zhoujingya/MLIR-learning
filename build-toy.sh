#!/usr/bin/bash

LLVM_TOOL_PATH=$HOME/tools/clang17
export PATH=$LLVM_TOOL_PATH/bin:$PATH

# Building toy dialect
mlir-tblgen -gen-op-decls include/Ops.td -I$LLVM_TOOL_PATH/include -o include/Ops.h.inc
mlir-tblgen -gen-op-defs include/Ops.td -I$LLVM_TOOL_PATH/include -o include/Ops.cpp.inc
mlir-tblgen -gen-dialect-decls include/Ops.td -I$LLVM_TOOL_PATH/include -o include/Dialect.h.inc
mlir-tblgen -gen-dialect-defs include/Ops.td -I$LLVM_TOOL_PATH/include -o include/Dialect.cpp.inc

cmake -B build \
    -S . \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug \
    -DLT_LLVM_INSTALL_DIR=$LLVM_TOOL_PATH\
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DLLVM_VERSION_=17 \
    -DCMAKE_BUILD_TYPE=Debug


cmake --build build