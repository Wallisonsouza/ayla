#include "celestia/debug/ast/AstDumper.hpp"
#include <format>

namespace celestia::debug {
void AstDumper::dump_identifier_pattern(const ast::IdentifierPatternNode *node) {

  auto g = context.object(std::format("IdentifierPattern(\"{}\")", node->name->str));

  g.field("TypeAnnotation", node->type_annotation);
}
} // namespace celestia::debug