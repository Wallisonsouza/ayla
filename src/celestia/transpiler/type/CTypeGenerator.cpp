#include "celestia/transpiler/CGenerator.hpp"

namespace celestia::codegen {
void CGenerator::generate_type(TypeId type_id) {

  if (!type_id.is_valid()) {
    out << "/* invalid type */";
    return;
  }

  const auto &type = context.compiler.types.get(type_id);

  switch (type.kind) {

  case semantic::TypeKind::Primitive: {
    const auto &primitive = static_cast<const semantic::PrimitiveType &>(type);

    switch (primitive.primitive) {
    case semantic::PrimitiveKind::Int: out << "int"; return;

    // case semantic::PrimitiveKind::Float:
    // case semantic::PrimitiveKind::Number: out << "float"; return;

    case semantic::PrimitiveKind::Bool: out << "bool"; return;

    case semantic::PrimitiveKind::Char: out << "char"; return;

    case semantic::PrimitiveKind::String: out << "char *"; return;

    case semantic::PrimitiveKind::Void: out << "void"; return;
    }

    return;
  }

  case semantic::TypeKind::Struct: {
    const auto &struct_type = static_cast<const semantic::StructType &>(type);

    auto *symbol = context.compiler.symbols.get(struct_type.symbol);

    if (!symbol) {
      out << "/* invalid struct */";
      return;
    }

    out << "struct " << symbol->name;
    return;
  }

  case semantic::TypeKind::GenericInstance: {
    const auto &generic = static_cast<const semantic::GenericInstanceType &>(type);

    // if (generic.constructor == context.compiler.builtins.array_symbol) {
    //   out << "AylaArray";
    //   return;
    // }

    // if (generic.constructor == context.compiler.builtins.ref_symbol) {
    //   if (generic.arguments.size() != 1) {
    //     out << "/* invalid ref */";
    //     return;
    //   }

    //   generate_type(generic.arguments[0]);
    //   out << " *";
    //   return;
    // }

    out << "/* unsupported generic type */";
    return;
  }

  case semantic::TypeKind::Function:
    // ...
    return;

  default: out << "/* unsupported type */"; return;
  }
}
} // namespace celestia::codegen