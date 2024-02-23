//===- standalone-opt.cpp ---------------------------------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "standalone/StandalonePasses.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/IR/Dialect.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/InitAllDialects.h"
#include "mlir/InitAllPasses.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Support/FileUtilities.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/ToolOutputFile.h"
#include <mlir/Parser/Parser.h>

#include "standalone/StandaloneDialect.h"
namespace cl = llvm::cl;
static cl::opt<std::string> inputFilename(cl::Positional,
                                          cl::desc("<input hello file>"),
                                          cl::init("-"),
                                          cl::value_desc("filename"));
static cl::opt<bool> enableConvertToLLVM("convert-to-llvm",
                                         cl::desc("Convert to LLVM IR"),
                                         cl::init(false));
int loadMLIR(mlir::MLIRContext &context,
             mlir::OwningOpRef<mlir::ModuleOp> &module) {
  llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>> fileOrErr =
      llvm::MemoryBuffer::getFileOrSTDIN(inputFilename);
  if (std::error_code ec = fileOrErr.getError()) {
    llvm::errs() << "Could not open input file: " << ec.message() << "\n";
    return -1;
  }

  llvm::SourceMgr sourceMgr;
  sourceMgr.AddNewSourceBuffer(std::move(*fileOrErr), llvm::SMLoc());
  module = mlir::parseSourceFile<mlir::ModuleOp>(sourceMgr, &context);
  if (!module) {
    llvm::errs() << "Error can't load file " << inputFilename << "\n";
    return 3;
  }
  return 0;
}

int loadAndProcessMLIR(mlir::MLIRContext &context,
                       mlir::OwningOpRef<mlir::ModuleOp> &module) {
  if (int error = loadMLIR(context, module)) {
    return error;
  }

  // Register passes to be applied in this compile process
  mlir::PassManager passManager(&context);
  mlir::applyPassManagerCLOptions(passManager);
  //   return 4;

  // passManager.addPass(mlir::createCanonicalizerPass());
  if(enableConvertToLLVM)
    passManager.addPass(standalone::createLowerToLLVMPass());
  passManager.addPass(standalone::createSimpleAttr());
  if (mlir::failed(passManager.run(*module))) {
    return 4;
  }

  return 0;
}
int main(int argc, char **argv) {
  // mlir::registerAllPasses();
  // // TODO: Register standalone passes here.

  // mlir::DialectRegistry registry;
  // mlir::MLIRContext context;
  // context.
  // mlir::PassManager passManager(&context);
  // registry.insert<mlir::standalone::StandaloneDialect,
  //                 mlir::arith::ArithDialect, mlir::func::FuncDialect>();
  // // Add the following to include *all* MLIR Core dialects, or selectively
  // // include what you need like above. You only need to register dialects
  // that
  // // will be *parsed* by the tool, not the one generated
  // // registerAllDialects(registry);

  // return mlir::asMainReturnCode(
  //     mlir::MlirOptMain(argc, argv, "Standalone optimizer driver\n",
  //     registry));
  mlir::registerMLIRContextCLOptions();
  mlir::registerPassManagerCLOptions();

  cl::ParseCommandLineOptions(argc, argv, "Standalone compiler\n");
  mlir::MLIRContext context;
  context.getOrLoadDialect<mlir::standalone::StandaloneDialect>();
  context.getOrLoadDialect<mlir::func::FuncDialect>();

  mlir::OwningOpRef<mlir::ModuleOp> module;
  if (int error = loadAndProcessMLIR(context, module)) {
    return error;
  }

  // dumpLLVMIR(*module);
  //  runJit(*module);

  return 0;
}
