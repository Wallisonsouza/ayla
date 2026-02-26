#include "semantic/checker/type_checker.hpp"

namespace ayla {

void Checker::check_pattern(ast::PatternNode *node) {
  if (!node) return;

  if (auto *idPattern = dynamic_cast<ast::IdentifierPatternNode *>(node)) {

    if (idPattern->type_annotation) check(idPattern->type_annotation);

    Type *finalType = nullptr;

    if (idPattern->type_annotation)
      finalType = idPattern->type_annotation->inferred_type;
    else if (idPattern->identifier && idPattern->identifier->inferred_type)
      finalType = idPattern->identifier->inferred_type;
    else
      finalType = &BuiltinTypes::Unknown;

    idPattern->inferred_type = finalType;

    if (auto *sym = unit.context.symbol_manager.get(idPattern->symbol_id)) sym->type = finalType;
  }
}

} // namespace ayla
