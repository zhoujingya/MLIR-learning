#!/usr/bin/bash

LLVM_TOOL_PATH=$HOME/tools/clang16
export PATH=$LLVM_TOOL_PATH/bin:$PATH

# Building standalone dialect
mlir-tblgen -gen-op-decls standalone/StandaloneOps.td -I$LLVM_TOOL_PATH/include -o standalone/StandaloneOps.h.inc
mlir-tblgen -gen-op-defs standalone/StandaloneOps.td -I$LLVM_TOOL_PATH/include -o standalone/StandaloneOps.cpp.inc
mlir-tblgen -gen-dialect-decls standalone/StandaloneDialect.td -I$LLVM_TOOL_PATH/include -o standalone/StandaloneDialect.h.inc
mlir-tblgen -gen-dialect-defs standalone/StandaloneDialect.td -I$LLVM_TOOL_PATH/include -o standalone/StandaloneDialect.cpp.inc

cmake -B build \
    -S . \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug \
    -DLT_LLVM_INSTALL_DIR=$LLVM_TOOL_PATH \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_BUILD_TYPE=Debug


cmake --build build