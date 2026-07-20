#pragma once

#include "ast/AstNode.hpp"
#include "ast/NodeKind.hpp"
#include "ast/names/NameNode.hpp"
#include <vector>

namespace ayla::ast {

struct QualifiedNameNode : AstNode {

  std::vector<NameNode *> parts;

  QualifiedNameNode(std::vector<NameNode *> parts) : AstNode(NodeKind::QualifiedName), parts(std::move(parts)) {}
};

} // namespace ayla::ast