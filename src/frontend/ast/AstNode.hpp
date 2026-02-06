#pragma once

#include "core/memory/type.hpp"
#include "core/node/flags.hpp"
#include "core/token/Location.hpp"
#include "frontend/ast/AstVisitor.hpp"
#include "frontend/ast/NodeKind.hpp"

namespace ayla::ast {

struct AstNode {
  NodeKind kind;
  SourceSlice slice;
  NodeFlag flags;
  Type *inferred_type = nullptr;
  virtual ~AstNode() = default;
  virtual void accept(AstVisitor &v) = 0;

protected:
  explicit AstNode(NodeKind k) : kind(k) {}
};

} // namespace ayla::ast