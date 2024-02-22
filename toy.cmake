include_directories(${CMAKE_BINARY_DIR}/include)
include_directories(${CMAKE_BINARY_DIR})
set(LLVM_TARGET_DEFINITIONS toy/ToyCombine.td)
mlir_tablegen(ToyCombine.inc -gen-rewriters)
add_public_tablegen_target(ToyCombineIncGen)

add_mlir_library(toy
    toy/AST.cpp
    toy/Dialect.cpp
    toy/MLIRGen.cpp
    toy/ToyCombine.cpp

    DEPENDS
    ToyOpsIncGen
    ToyCombineIncGen
)

add_executable(mlir-toy toy/toy.cpp)
target_link_libraries(mlir-toy toy)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
