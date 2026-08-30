#pragma once

#include "celestia/ast/NodeKind.hpp"
#include "celestia/semantic/id/ids.hpp"
#include "celestia/core/token/Location.hpp"

namespace celestia::ast {

struct Node {

  const NodeKind kind;

  SourceSlice slice;

  semantic::SymbolId symbol_id;
  
  semantic::TypeId type_id;

  virtual ~Node() = default;
  

protected:
  explicit Node(NodeKind k) : kind(k), symbol_id(semantic::SymbolId::invalid()), type_id(semantic::TypeId::invalid()) {}
};

} // namespace celestia::ast