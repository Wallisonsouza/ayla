#pragma once

#include "NodeState.hpp"
#include "celestia/ast/NodeKind.hpp"
#include "celestia/core/token/Location.hpp"

struct Type;

namespace celestia::ast {

struct Node {
  const NodeKind kind;
  SourceSlice slice;
  NodeState flags;
  Type *inferred_type = nullptr;
  virtual ~Node() = default;

protected:
  explicit Node(NodeKind k) : kind(k) {}
};

} // namespace celestia::ast

