#pragma once

#include "celestia/core/ids/Ids.hpp"

#include <unordered_map>

namespace celestia {

enum class IntrinsicKind {
  None,

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

  Array,
  Ref
};

class IntrinsicRegistry {
public:
  void bind(SymbolId symbol, IntrinsicKind intrinsic) { intrinsics[symbol] = intrinsic; }

  IntrinsicKind get(SymbolId symbol) const {
    auto it = intrinsics.find(symbol);

    if (it == intrinsics.end()) return IntrinsicKind::None;

    return it->second;
  }

  bool is_intrinsic(SymbolId symbol) const { return intrinsics.contains(symbol); }

private:
  std::unordered_map<SymbolId, IntrinsicKind> intrinsics;
};

} // namespace celestia