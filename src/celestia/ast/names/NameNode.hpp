#pragma once
#include "celestia/ast/AstNode.hpp"

namespace celestia::ast {

struct NameNode : AstNode {
  explicit NameNode(NodeKind k) : AstNode(k) {}
};

} // namespace celestia::ast