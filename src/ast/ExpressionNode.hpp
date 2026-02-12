#pragma once

#include "ast/AstNode.hpp"
#include "semantic/symbols/SymbolId.hpp"

namespace ayla::ast {

struct ExpressionNode : AstNode {

  SymbolId resolved_symbol_id;
  explicit ExpressionNode(NodeKind k) : AstNode(k) {}
};

} // namespace ayla::ast