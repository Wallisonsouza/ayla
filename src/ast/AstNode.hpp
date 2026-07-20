#pragma once

#include "ast/NodeKind.hpp"
#include "NodeState.hpp"
#include "core/token/Location.hpp"

struct Type;

namespace ayla::ast {

struct AstNode {
  const NodeKind kind;
  SourceSlice slice;
  NodeState flags;
  Type *inferred_type = nullptr;
  virtual ~AstNode() = default;

protected:
  explicit AstNode(NodeKind k) : kind(k) {}
};

} // namespace ayla::ast