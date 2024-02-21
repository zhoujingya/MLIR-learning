
get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)
include_directories(${PROJECT_SOURCE_DIR}/standalone)
set(LIBS
        ${dialect_libs}
        ${conversion_libs}
        MLIRStandalone
        MLIRAnalysis
        MLIRCallInterfaces
        MLIRCastInterfaces
        MLIRExecutionEngine
        MLIRIR
        MLIRLLVMCommonConversion
        MLIRLLVMToLLVMIRTranslation
        MLIRMemRefDialect
        MLIRLLVMDialect
        MLIRParser
        MLIRPass
        MLIRSideEffectInterfaces
        MLIRSupport
        MLIRTargetLLVMIRExport
        MLIRTransforms
        MLIROptLib
        )
add_llvm_executable(standalone-opt standalone-opt.cpp)
target_link_directories(standalone-opt PUBLIC "/home/triton/othes/MLIR-learning/build/standalone")
llvm_update_compile_flags(standalone-opt)
target_link_libraries(standalone-opt PRIVATE ${LIBS})

mlir_check_all_link_libraries(standalone-opt)