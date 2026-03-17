#include "ast_debug.hpp"

void ASTDebug::debug_pattern(const ayla::ast::PatternNode *node) {

  switch (node->kind) {

  case ayla::ast::NodeKind::IdentifierPattern: {

    auto pattern = static_cast<const ayla::ast::IdentifierPatternNode *>(node);

    debug_header("IdentifierPattern: " + pattern->identifier->name);

    debug_node(pattern->type_annotation, true);
  }

  default:
    break;
  }
}