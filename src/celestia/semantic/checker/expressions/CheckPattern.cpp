#include "celestia/semantic/checker/TypeChecker.hpp"

namespace celestia::semantic {

TypeId TypeChecker::check_pattern(ast::PatternNode *pattern, TypeId expected_type) {

  if (!pattern) return TypeId::invalid();

  switch (pattern->kind) {

  case ast::NodeKind::NamedPattern: return check_name_pattern(static_cast<ast::NamedPattern *>(pattern), expected_type);

  default: error(pattern, "unsupported pattern: " + std::string(ast::node_kind_name(pattern->kind))); return TypeId::invalid();
  }
}

TypeId TypeChecker::check_name_pattern(ast::NamedPattern *pattern, TypeId expected_type) {

  if (!pattern) return TypeId::invalid();

  if (!pattern->symbol_id.is_valid()) {

    error(pattern, "pattern has invalid SymbolId");

    return TypeId::invalid();
  }

  auto *symbol = context.compiler.symbols.get(pattern->symbol_id);

  if (!symbol) {

    error(pattern, "pattern symbol not found");

    return TypeId::invalid();
  }

  // ------------------------------------------------
  // Tipo da anotação
  // ------------------------------------------------

  TypeId annotation_type = TypeId::invalid();

  if (pattern->type_annotation) {

    annotation_type = type_from_node(pattern->type_annotation);

    if (!annotation_type.is_valid()) {

      error(pattern, "invalid pattern type annotation");

      return TypeId::invalid();
    }
  }

  // ------------------------------------------------
  // Determina o tipo
  // ------------------------------------------------

  TypeId type = annotation_type;

  // Sem anotação:
  // usa o tipo fornecido pelo contexto.
  if (!type.is_valid()) {

    if (!expected_type.is_valid()) {

      error(pattern, "cannot infer pattern type");

      return TypeId::invalid();
    }

    type = expected_type;
  }

  // ------------------------------------------------
  // Anotação + tipo esperado
  // ------------------------------------------------

  if (annotation_type.is_valid() && expected_type.is_valid()) {

    if (!is_assignable(annotation_type, expected_type)) {

      error(pattern, "pattern type is not compatible "
                     "with expected type");

      return TypeId::invalid();
    }
  }

  // ------------------------------------------------
  // Resultado semântico
  // ------------------------------------------------

  pattern->type_id = type;
  symbol->type = type;

  return type;
}

} // namespace celestia::semantic