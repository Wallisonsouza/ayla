#pragma once
#include "celestia/ast/names/NameNode.hpp"
#include "string"

namespace celestia::ast {


struct IdentifierNode : NameNode {
  std::string str;
  
  
  explicit IdentifierNode(std::string n) : NameNode(NodeKind::Identifier), str(std::move(n)) {}
};


} // namespace celestia::ast