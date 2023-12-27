/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {
namespace standalone {

class StandaloneDialect : public ::mlir::Dialect {
  explicit StandaloneDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~StandaloneDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("standalone");
  }
};
} // namespace standalone
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::standalone::StandaloneDialect)
