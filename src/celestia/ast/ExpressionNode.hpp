#pragma once

#include "celestia/ast/AstNode.hpp"
#include "celestia/semantic/symbols/SymbolId.hpp"

namespace celestia::ast {

struct ExpressionNode : AstNode {

  SymbolId resolved_symbol_id;
  explicit ExpressionNode(NodeKind k) : AstNode(k) {}
};

} // namespace celestia::ast