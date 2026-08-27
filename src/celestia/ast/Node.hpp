#pragma once

#include "celestia/ast/NodeKind.hpp"
#include "celestia/core/ids/Ids.hpp"
#include "celestia/core/token/Location.hpp"

namespace celestia::ast {

struct Node {

  const NodeKind kind;

  SourceSlice slice;

  SymbolId symbol_id;
  TypeId type_id;

  virtual ~Node() = default;

protected:
  explicit Node(NodeKind k) : kind(k), symbol_id(SymbolId::invalid()), type_id(TypeId::invalid()) {}
};

} // namespace celestia::ast