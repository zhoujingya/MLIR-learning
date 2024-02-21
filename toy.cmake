include_directories(${CMAKE_BINARY_DIR}/include)
add_mlir_library(toy
    toy/AST.cpp
    toy/Dialect.cpp
    toy/MLIRGen.cpp

    DEPENDS
    ToyOpsIncGen
)

add_executable(mlir-toy toy/toy.cpp)
target_link_libraries(mlir-toy toy)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
