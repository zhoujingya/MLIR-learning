cmake_minimum_required(VERSION 3.22)

project(mlir-learning VERSION 1.0.0)

# We will use llvm library, so we need to link llvm libraries

set(LT_LLVM_INCLUDE_DIR "${LT_LLVM_INSTALL_DIR}/include")

list(APPEND CMAKE_PREFIX_PATH "${LT_LLVM_INSTALL_DIR}/lib/cmake/llvm/")

find_package(LLVM 16 REQUIRED CONFIG)

# Here need to check llvm version
if(NOT "16" VERSION_EQUAL "${LLVM_VERSION_MAJOR}")
  message(FATAL_ERROR "Found LLVM ${LLVM_VERSION_MAJOR}, but need LLVM 16")
endif()

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
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS} )

# NOTE: Very important for building this program
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

# Add source files
file(GLOB_RECURSE SOURCE src/*.cpp)

add_executable(mlir-toy ${SOURCE})

target_include_directories(mlir-toy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_directories(mlir-toy PRIVATE ${LT_LLVM_INSTALL_DIR}/lib)

target_link_libraries(mlir-toy PRIVATE MLIRSupport LLVMCore LLVMSupport)
