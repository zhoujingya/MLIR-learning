//===- StandaloneDialect.cpp - Standalone dialect ---------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "StandaloneDialect.h"
#include "StandaloneOps.h"

using namespace mlir;
using namespace mlir::standalone;

#include "standalone/StandaloneDialect.cpp.inc"

//===----------------------------------------------------------------------===//
// Standalone dialect.
//===----------------------------------------------------------------------===//

void StandaloneDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "standalone/StandaloneOps.cpp.inc"
      >();
}
