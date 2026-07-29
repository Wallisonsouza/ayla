#pragma once

#include "ast/names/IdentifierNode.hpp"
#include "ast/names/NameNode.hpp"
#include <string>
#include <vector>

namespace ayla::ast {

struct QualifiedNameNode : NameNode {

  std::vector<IdentifierNode *> parts;

  std::string get_name() {
    std::string key;

    for (size_t i = 0; i < parts.size(); i++) {
      if (i > 0) key += ".";

      key += parts[i]->str;
    }

    return key;
  }

  QualifiedNameNode(std::vector<IdentifierNode *> parts) : NameNode(NodeKind::QualifiedName), parts(std::move(parts)) {}
};

} // namespace ayla::ast