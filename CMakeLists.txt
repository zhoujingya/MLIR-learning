cmake_minimum_required(VERSION 3.22)

project(mlir-learning VERSION 1.0.0)

# We will use llvm library, so we need to link llvm libraries

set(LT_LLVM_INCLUDE_DIR "${LT_LLVM_INSTALL_DIR}/include")

list(APPEND CMAKE_PREFIX_PATH "${LT_LLVM_INSTALL_DIR}/lib/cmake/llvm/")

find_package(LLVM ${LLVM_VERSION_} REQUIRED CONFIG)


message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LT_LLVM_INSTALL_DIR}")

message("LLVM STATUS:
  Definitions ${LLVM_DEFINITIONS}
  Includes    ${LLVM_INCLUDE_DIRS}
  Libraries   ${LLVM_LIBRARY_DIRS}
  Targets     ${LLVM_TARGETS_TO_BUILD}"
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Set the LLVM header and library paths
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})

# NOTE: Very important for building this program
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

link_directories(${LT_LLVM_INSTALL_DIR}/lib)

link_libraries(
  LLVMCore
  LLVMSupport
  MLIRAnalysis
  MLIRIR
  MLIRParser
  MLIRSideEffectInterfaces
  MLIRTransforms
)
if(${LLVM_VERSION_MAJOR} VERSION_EQUAL "17")
  file(GLOB_RECURSE SOURCE toy/*.cpp)
  add_executable(mlir-toy ${SOURCE})
  target_include_directories(mlir-toy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

# Add source files


add_subdirectory(others)
if(${LLVM_VERSION_MAJOR} VERSION_EQUAL "16")
  add_subdirectory(standalone)
endif()