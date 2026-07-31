#pragma once

#include "NodeState.hpp"
#include "celestia/ast/NodeKind.hpp"
#include "celestia/core/token/Location.hpp"

struct Type;

namespace celestia::ast {

struct AstNode {
  const NodeKind kind;
  SourceSlice slice;
  NodeState flags;
  Type *inferred_type = nullptr;
  virtual ~AstNode() = default;

protected:
  explicit AstNode(NodeKind k) : kind(k) {}
};

} // namespace celestia::ast

