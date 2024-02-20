
find_package(MLIR REQUIRED CONFIG)
# Append function list and include
list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
include(TableGen)
include(AddLLVM) # LLVM stuff
include(AddMLIR) # MLIR stuff
include(HandleLLVMOptions)
message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)
set(LLVM_TARGET_DEFINITIONS StandaloneDialect.td)
# mlir_tablegen(StandaloneOps.h.inc -gen-op-decls)
# mlir_tablegen(StandaloneOps.cpp.inc -gen-op-defs)
# mlir_tablegen(StandaloneDialect.h.inc -gen-dialect-decls)
# mlir_tablegen(StandaloneDialect.cpp.inc -gen-op-defs)
# add_library(MLIRStandalone SHARED StandaloneDialect.cpp StandaloneOps.cpp LowerToLLVM.cpp)
add_mlir_dialect_library(MLIRStandalone
                        StandaloneDialect.cpp
                        StandaloneOps.cpp
                        LowerToLLVM.cpp
                        createSimpleAttr.cpp

        ADDITIONAL_HEADER_DIRS
        ${PROJECT_SOURCE_DIR}/standalone

	LINK_LIBS PUBLIC
	MLIRIR
	)
# set(LIBS
#         ${dialect_libs}
#         ${conversion_libs}
#         MLIRArithDialect
#         MLIROptLib
#         MLIRStandalone
#         MLIRAnalysis
#         MLIRCallInterfaces
#         MLIRCastInterfaces
#         MLIRExecutionEngine
#         MLIRIR
#         MLIRLLVMCommonConversion
#         MLIRLLVMToLLVMIRTranslation
#         MLIRMemRefDialect
#         MLIRLLVMDialect
#         MLIRParser
#         MLIRPass
#         MLIRSideEffectInterfaces
#         MLIRSupport
#         MLIRTargetLLVMIRExport
#         MLIRTransforms
#         MLIROptLib
#         MLIRLLVMCommonConversion
#         MLIRControlFlowDialect
#         MLIRLLVMDialect
#         )

# add_executable(standalone-opt standalone-opt.cpp)
# target_link_directories(standalone-opt PUBLIC "/home/triton/othes/MLIR-learning/build/lib")
# target_link_libraries(standalone-opt PRIVATE ${LIBS})
