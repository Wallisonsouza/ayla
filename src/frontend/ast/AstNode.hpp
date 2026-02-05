#pragma once

#include "core/memory/type.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/flags.hpp"
#include "core/token/Location.hpp"

namespace ayla::ast {

struct AstNode {
  core::ast::NodeKind kind;
  SourceSlice slice;
  NodeFlag flags;

  Type *inferred_type;

  virtual ~AstNode() = default;

protected:
  explicit AstNode(core::ast::NodeKind k) : kind(k) {}
};

} // namespace ayla::ast
