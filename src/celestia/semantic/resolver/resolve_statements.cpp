#include "celestia/semantic/resolver/Resolver.hpp"

void Resolver::if_statement(celestia::ast::node::IfStatementNode *node) {
  if (!node) return;

  if (node->condition) { resolve(node->condition); }

  if (node->then_block) { resolve(node->then_block); }

  if (node->else_block) { resolve(node->else_block); }
}

void Resolver::while_statement(celestia::ast::node::WhileStatementNode *node) {
  if (!node) return;

  if (node->condition) { resolve(node->condition); }

  if (node->body) { resolve(node->body); }
}

void Resolver::expression_statement(celestia::ast::node::ExpressionStatementNode *node) {

  if (node->expression) { resolve(node->expression); }
}

void Resolver::block(celestia::ast::node::BlockStatementNode *node) {

  auto *scope = context.unit.scopes.create_scope(context.scopes.current());

  for (auto *stmt : node->statements) { resolve(stmt); }

}

void Resolver::return_statement(celestia::ast::node::ReturnStatementNode *node) {
  if (node->value) { resolve(node->value); }
}