#pragma once

#include "ast/names/NameNode.hpp"
#include <vector>
#include "ast/names/IdentifierNode.hpp"

namespace ayla::ast {

struct QualifiedNameNode : NameNode {

  std::vector<IdentifierNode *> parts;

  QualifiedNameNode(std::vector<IdentifierNode *> parts) : NameNode(NodeKind::QualifiedName), parts(std::move(parts)) {}
};

} // namespace ayla::ast