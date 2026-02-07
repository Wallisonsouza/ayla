#include "ast_debug.hpp"
#include "frontend/ast/NodeKind.hpp"
#include "frontend/ast/PatternNode.hpp"
#include <iostream>

void ASTDebug::debug_pattern(const ayla::ast::PatternNode *node) {

  debug_header("PatternNode");

  switch (node->kind) {

  case ayla::ast::NodeKind::IdentifierPattern: {

    auto pattern = static_cast<const ayla::ast::IdentifierPatternNode *>(node);

    std::cout << pattern->identifier;
  }

  default: break;
  }
}
