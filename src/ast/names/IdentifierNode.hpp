#pragma once
#include "ast/names/NameNode.hpp"
#include "string"

namespace ayla::ast {


struct IdentifierNode : NameNode {
  std::string str;
  explicit IdentifierNode(std::string n) : NameNode(NodeKind::Identifier), str(std::move(n)) {}
};


} // namespace ayla::ast