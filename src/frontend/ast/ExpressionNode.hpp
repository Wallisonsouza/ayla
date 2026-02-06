#pragma once

#include "core/memory/SymbolId.hpp"
#include "frontend/ast/AstNode.hpp"

namespace ayla::ast {

struct ExpressionNode : AstNode {

  SymbolId resolved_symbol_id;

  explicit ExpressionNode(NodeKind k) : AstNode(k) {}
};

} // namespace ayla::ast