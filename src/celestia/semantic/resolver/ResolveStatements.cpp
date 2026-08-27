#include "celestia/semantic/resolver/Resolver.hpp"

#include <iostream>
namespace celestia::semantic {
void Resolver::if_statement(celestia::ast::IfStatement *node) {
  if (node->condition) { resolve(node->condition); }

  if (node->then_block) { resolve(node->then_block); }

  if (node->else_block) { resolve(node->else_block); }
}

void Resolver::while_statement(celestia::ast::WhileStatement *node) {
  if (node->condition) { resolve(node->condition); }

  if (node->body) { resolve(node->body); }
}

void Resolver::expression_statement(celestia::ast::ExpressionStatement *node) {

  if (node->expression) { resolve(node->expression); }
}


void Resolver::block_statement(celestia::ast::BlockStatement *node) {

  if (!node) return;

  auto *parent = context.scopes.current();

  if (!parent) {
    std::cout << "ERRO: bloco sem scope pai\n";
    return;
  }

  auto *scope = context.unit.module->scopes.create_scope(core::ScopeKind::Block, parent);

  if (!scope) {
    std::cout << "ERRO: nao foi possivel criar scope\n";
    return;
  }

  // context.scopes.push(*scope);

  // for (auto *stmt : node->statements) {

  //   if (!stmt) {
  //     std::cout << "ERRO: statement nulo no bloco\n";
  //     continue;
  //   }

  //   resolve(stmt);
  // }

  // context.scopes.pop();
}

} // namespace celestia::semantic