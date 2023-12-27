//===- StandaloneOps.cpp - Standalone dialect ops ---------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "dialect/StandaloneOps.h"
#include "dialect/StandaloneDialect.h"
#include "mlir/IR/OpImplementation.h"

#define GET_OP_CLASSES
#include "dialect/StandaloneOps.cpp.inc"
