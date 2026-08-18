#include "celestia/semantic/resolver/Resolver.hpp"

#include <iostream>
namespace celestia::semantic {
void Resolver::identifier(celestia::ast::IdentifierExpressionNode *node) {
  if (!node) return;

  SymbolId id = context.scopes.current()->symbol(node->name->str);

  if (!id.is_valid()) {
    std::cout << "ERRO: simbolo nao declarado: " << node->name->str << '\n';
    return;
  }

  node->symbol_id = id;
}

void Resolver::number_literal(celestia::ast::NumberLiteralNode *node) {}

void Resolver::string_literal(celestia::ast::StringLiteralNode *node) {}

void Resolver::boolean_literal(celestia::ast::BoolLiteralNode *node) {}

void Resolver::object_literal(celestia::ast::ObjectLiteralNode *node) {

  if (!node) return;

  for (auto *field : node->fields) {
    if (field && field->value) resolve(field->value);
  }
}

void Resolver::array_literal(celestia::ast::ArrayLiteralNode *node) {
  if (!node) return;

  for (auto *element : node->elements) {
    if (element) resolve(element);
  }
}
}