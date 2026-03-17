#pragma once

#include "ast/AstVisitor.hpp"
#include "ast/NodeKind.hpp"
#include "ayla/source/source_location.hpp"
#include "core/node/flags.hpp"

struct Type;

namespace ayla::ast {

struct AstNode {
  NodeKind kind;
  SourceSlice slice;
  NodeFlag flags;
  Type *inferred_type = nullptr;
  uint16_t local_slot = UINT16_MAX;
  virtual ~AstNode() = default;
  virtual void accept(AstVisitor &v) = 0;

protected:
  explicit AstNode(NodeKind k) : kind(k) {}
};

} // namespace ayla::ast