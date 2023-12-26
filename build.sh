#!/usr/bin/bash

LLVM_TOOL_PATH=$HOME/tools/clang16
export PATH=$LLVM_TOOL_PATH/bin:$PATH

# Building toy dialect
mlir-tblgen -gen-op-decls dialect/Ops.td -I$LLVM_TOOL_PATH/include -o dialect/Ops.h.inc
mlir-tblgen -gen-op-defs dialect/Ops.td -I$LLVM_TOOL_PATH/include -o dialect/Ops.cpp.inc
mlir-tblgen -gen-dialect-decls dialect/Ops.td -I$LLVM_TOOL_PATH/include -o dialect/Dialect.h.inc
mlir-tblgen -gen-dialect-defs dialect/Ops.td -I$LLVM_TOOL_PATH/include -o dialect/Dialect.cpp.inc

cmake -B build \
    -S . \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug \
    -DLT_LLVM_INSTALL_DIR=$HOME/tools/clang16 \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake --build build