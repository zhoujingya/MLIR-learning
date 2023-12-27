/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::standalone::StandaloneDialect)
namespace mlir {
namespace standalone {

StandaloneDialect::StandaloneDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<StandaloneDialect>()) {
  
  initialize();
}

StandaloneDialect::~StandaloneDialect() = default;

} // namespace standalone
} // namespace mlir
