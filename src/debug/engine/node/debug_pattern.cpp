#include "ast/NodeKind.hpp"
#include "ast/patterns/PatternNode.hpp"
#include "ast_debug.hpp"

void ASTDebug::debug_pattern(const ayla::ast::PatternNode *node) {

  switch (node->kind) {

  case ayla::ast::NodeKind::IdentifierPattern: {

    auto pattern = static_cast<const ayla::ast::IdentifierPatternNode *>(node);

    debug_header("IdentifierPattern: " + pattern->name->str);

    debug_node(pattern->type_annotation, true);
  }

  default: break;
  }
}