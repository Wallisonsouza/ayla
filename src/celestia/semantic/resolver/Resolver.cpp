#include "Resolver.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"

Resolver::Resolver(ResolverContext &ctx) : context(ctx), handlers(this) {
  handlers.bind<celestia::ast::node::NumberLiteralNode>(&Resolver::number_literal);
  handlers.bind<celestia::ast::node::StringLiteralNode>(&Resolver::string_literal);
  handlers.bind<celestia::ast::node::BoolLiteralNode>(&Resolver::boolean_literal);

  handlers.bind<celestia::ast::node::BinaryExpressionNode>(&Resolver::binary_expression);
  handlers.bind<celestia::ast::node::UnaryExpressionNode>(&Resolver::unary_expression);
  handlers.bind<celestia::ast::node::AssignmentExpressionNode>(&Resolver::assignment);

  handlers.bind<celestia::ast::node::CallExpressionNode>(&Resolver::function_call);
  handlers.bind<celestia::ast::node::MemberAccessExpressionNode>(&Resolver::member_access);
  handlers.bind<celestia::ast::node::IndexAccessExpressionNode>(&Resolver::index_access);

  handlers.bind<celestia::ast::node::IdentifierExpressionNode>(&Resolver::identifier);

  handlers.bind<celestia::ast::node::IfStatementNode>(&Resolver::if_statement);
  handlers.bind<celestia::ast::node::WhileStatementNode>(&Resolver::while_statement);
  handlers.bind<celestia::ast::node::BlockStatementNode>(&Resolver::block);
  handlers.bind<celestia::ast::node::ExpressionStatementNode>(&Resolver::expression_statement);
  handlers.bind<celestia::ast::node::ReturnStatementNode>(&Resolver::return_statement);

  handlers.bind<celestia::ast::node::VariableDeclarationNode>(&Resolver::variable_declaration);
  handlers.bind<celestia::ast::node::FunctionDeclarationNode>(&Resolver::function_declaration);
  handlers.bind<celestia::ast::node::ModuleDeclarationNode>(&Resolver::module_declaration);
  handlers.bind<celestia::ast::node::ImportDeclarationNode>(&Resolver::import_declaration);

  handlers.bind<celestia::ast::node::ArrayLiteralNode>(&Resolver::array_literal);
  handlers.bind<celestia::ast::node::ObjectLiteralNode>(&Resolver::object_literal);

  handlers.bind<celestia::ast::TypeNode>(&Resolver::type_node);
}

void Resolver::resolve(celestia::ast::AstNode *node) {

  auto *root = context.unit.ast.get_root();

  if (!node || node->flags.has(NodeFlags::Resolved)) return;

  node->flags.add(NodeFlags::Resolved);

  handlers.dispatch(node);
}