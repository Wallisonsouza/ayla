#pragma once
#include "ast/AstNode.hpp"

namespace ayla::ast {

struct NameNode : AstNode {
  explicit NameNode(NodeKind k) : AstNode(k) {}
};

} // namespace ayla::ast