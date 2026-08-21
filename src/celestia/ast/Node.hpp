#pragma once

#include "celestia/ast/NodeKind.hpp"
#include "celestia/core/token/Location.hpp"
#include "celestia/semantic/symbol/SymbolId.hpp"

struct Type;

namespace celestia::ast {

struct Node {
  const NodeKind kind;
  SourceSlice slice;
  SymbolId symbol_id;
  Type *inferred_type = nullptr;
  virtual ~Node() = default;

protected:
  explicit Node(NodeKind k) : kind(k) {}
};

} // namespace celestia::ast

