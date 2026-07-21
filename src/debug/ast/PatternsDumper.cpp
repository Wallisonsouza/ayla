#include "AstDumper.hpp"

void AstDumper::debug_pattern(const ayla::ast::PatternNode *node) {

  switch (node->kind) {

  case ayla::ast::NodeKind::IdentifierPattern: {

    auto pattern = static_cast<const ayla::ast::IdentifierPatternNode *>(node);

    if (pattern->name) { debug_header(std::format("IdentifierPattern(\"{}\")", pattern->name->str)); }

    if (pattern->type_annotation) { debug_node(pattern->type_annotation, true); }
  }

  default: break;
  }
}