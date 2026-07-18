#pragma once

#include "ast/AstVisitor.hpp"
#include "ast/NodeKind.hpp"
#include "NodeState.hpp"
#include "core/token/Location.hpp"

struct Type;

namespace ayla::ast {

struct AstNode {
  NodeKind kind;
  SourceSlice slice;
  NodeState flags;
  Type *inferred_type = nullptr;
  virtual ~AstNode() = default;
  virtual void accept(AstVisitor &v) = 0;

protected:
  explicit AstNode(NodeKind k) : kind(k) {}
};

} // namespace ayla::ast