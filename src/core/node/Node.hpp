#pragma once

#include "NodeKind.hpp"
#include "ayla-source/source.hpp"
#include "core/memory/type.hpp"
#include "core/node/flags.hpp"

namespace core::ast {

struct ASTNode {
  NodeKind kind;
  NodeKindBase base_kind;
  ayla::source::SourceSlice slice;
  NodeFlag flags;

  Type *inferred_type;

  virtual ~ASTNode() = default;

protected:
  explicit ASTNode(NodeKindBase base, NodeKind k) : base_kind(base), kind(k) {}
};

} // namespace core::ast
