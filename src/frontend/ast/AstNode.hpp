#pragma once

#include "core/node/flags.hpp"
#include "core/token/Location.hpp"
#include "frontend/ast/NodeKind.hpp"

namespace ayla::ast {

struct AstNode {
  NodeKind kind;
  SourceSlice slice;
  NodeFlag flags;

  virtual ~AstNode() = default;

protected:
  explicit AstNode(NodeKind k) : kind(k) {}
};

} // namespace ayla::ast