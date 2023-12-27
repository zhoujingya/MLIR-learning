get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)
add_library(MLIRStandalone SHARED StandaloneDialect.cpp StandaloneOps.cpp)
set(LIBS
        ${dialect_libs}
        ${conversion_libs}
        MLIRArithDialect
        MLIROptLib
        MLIRStandalone
        )

add_executable(standalone-opt standalone-opt.cpp)
target_link_directories(standalone-opt PUBLIC "/home/triton/othes/MLIR-learning/build/lib")
target_link_libraries(standalone-opt PRIVATE ${LIBS})
