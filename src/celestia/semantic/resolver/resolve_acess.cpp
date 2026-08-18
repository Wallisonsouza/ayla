#include "celestia/ast/expressions/MemberAccessExpressionNode.hpp"
#include "celestia/semantic/resolver/Resolver.hpp"
#include <iostream>
namespace celestia::semantic {
void Resolver::index_access(celestia::ast::IndexAccessExpressionNode *node) {

  if (node->base) resolve(node->base);

  if (node->index) resolve(node->index);
}

void Resolver::member_access(celestia::ast::MemberAccessExpressionNode *node) {
  if (!node || !node->base || !node->member) return;

  resolve(node->base);

  if (!node->base->symbol_id.is_valid()) {

    std::cout << "ERRO: membro acessado em simbolo invalido\n";

    return;
  }

  node->symbol_id = node->base->symbol_id;
}

void Resolver::function_call(celestia::ast::CallExpressionNode *node) {

  if (node->callee) resolve(node->callee);

  for (auto *arg : node->arguments) { resolve(arg); }
}
} // namespace celestia::semantic