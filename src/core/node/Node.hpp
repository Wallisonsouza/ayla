#pragma once

#include "NodeKind.hpp"
#include "core/memory/type.hpp"
#include "core/node/flags.hpp"
#include "core/token/Location.hpp"

namespace core::ast {

struct ASTNode {
  NodeKind kind;
  NodeKindBase base_kind;
  SourceSlice slice;
  NodeFlag flags;
  bool resolved = false;
  Type *inferred_type;

  virtual ~ASTNode() = default;

protected:
  explicit ASTNode(NodeKindBase base, NodeKind k) : base_kind(base), kind(k) {}
};

} // namespace core::ast
