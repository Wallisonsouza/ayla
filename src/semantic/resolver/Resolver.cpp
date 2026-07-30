#include "Resolver.hpp"
#include "ast/statements/BlockStatementNode.hpp"

Resolver::Resolver(ResolverContext &ctx) : context(ctx), handlers(this) {
  handlers.bind<ayla::ast::node::NumberLiteralNode>(&Resolver::number_literal);
  handlers.bind<ayla::ast::node::StringLiteralNode>(&Resolver::string_literal);
  handlers.bind<ayla::ast::node::BoolLiteralNode>(&Resolver::boolean_literal);

  handlers.bind<ayla::ast::node::BinaryExpressionNode>(&Resolver::binary_expression);
  handlers.bind<ayla::ast::node::UnaryExpressionNode>(&Resolver::unary_expression);
  handlers.bind<ayla::ast::node::AssignmentExpressionNode>(&Resolver::assignment);

  handlers.bind<ayla::ast::node::CallExpressionNode>(&Resolver::function_call);
  handlers.bind<ayla::ast::node::MemberAccessExpressionNode>(&Resolver::member_access);
  handlers.bind<ayla::ast::node::IndexAccessExpressionNode>(&Resolver::index_access);

  handlers.bind<ayla::ast::node::IdentifierExpressionNode>(&Resolver::identifier);

  handlers.bind<ayla::ast::node::IfStatementNode>(&Resolver::if_statement);
  handlers.bind<ayla::ast::node::WhileStatementNode>(&Resolver::while_statement);
  handlers.bind<ayla::ast::node::BlockStatementNode>(&Resolver::block);
  handlers.bind<ayla::ast::node::ExpressionStatementNode>(&Resolver::expression_statement);
  handlers.bind<ayla::ast::node::ReturnStatementNode>(&Resolver::return_statement);

  handlers.bind<ayla::ast::node::VariableDeclarationNode>(&Resolver::variable_declaration);
  handlers.bind<ayla::ast::node::FunctionDeclarationNode>(&Resolver::function_declaration);
  handlers.bind<ayla::ast::node::ModuleDeclarationNode>(&Resolver::module_declaration);
  handlers.bind<ayla::ast::node::ImportDeclarationNode>(&Resolver::import_declaration);

  handlers.bind<ayla::ast::node::ArrayLiteralNode>(&Resolver::array_literal);
  handlers.bind<ayla::ast::node::ObjectLiteralNode>(&Resolver::object_literal);

  handlers.bind<ayla::ast::TypeNode>(&Resolver::type_node);
}

void Resolver::resolve(ayla::ast::AstNode *node) {

  auto *root = context.unit.ast.get_root();

  if (!node || node->flags.has(NodeFlags::Resolved)) return;

  node->flags.add(NodeFlags::Resolved);

  handlers.dispatch(node);
}