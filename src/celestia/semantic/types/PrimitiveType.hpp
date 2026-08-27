#pragma once

#include <string_view>

namespace celestia::semantic {

enum class PrimitiveKind {
  Int,
  UInt,

  Int8,
  Int16,
  Int32,
  Int64,

  UInt8,
  UInt16,
  UInt32,
  UInt64,

  F32,
  F64,

  Bool,
  Char,
  String,
  Void,
};

constexpr std::string_view primitive_kind_name(PrimitiveKind kind) {
  switch (kind) {
  case PrimitiveKind::Int:    return "int";
  case PrimitiveKind::UInt:   return "uint";

  case PrimitiveKind::Int8:   return "int8";
  case PrimitiveKind::Int16:  return "int16";
  case PrimitiveKind::Int32:  return "int32";
  case PrimitiveKind::Int64:  return "int64";

  case PrimitiveKind::UInt8:  return "uint8";
  case PrimitiveKind::UInt16: return "uint16";
  case PrimitiveKind::UInt32: return "uint32";
  case PrimitiveKind::UInt64: return "uint64";

  case PrimitiveKind::F32:    return "f32";
  case PrimitiveKind::F64:    return "f64";

  case PrimitiveKind::Bool:   return "bool";
  case PrimitiveKind::Char:   return "char";
  case PrimitiveKind::String: return "string";
  case PrimitiveKind::Void:   return "void";
  }

  return "<unknown>";
}

} // namespace celestia::semantic