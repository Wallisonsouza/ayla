#include "Resolver.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"

Resolver::Resolver(ResolverContext &ctx) : context(ctx), handlers(this) {
  handlers.bind<celestia::ast::NumberLiteralNode>(&Resolver::number_literal);
  handlers.bind<celestia::ast::StringLiteralNode>(&Resolver::string_literal);
  handlers.bind<celestia::ast::BoolLiteralNode>(&Resolver::boolean_literal);

  handlers.bind<celestia::ast::BinaryExpressionNode>(&Resolver::binary_expression);
  handlers.bind<celestia::ast::UnaryExpressionNode>(&Resolver::unary_expression);
  handlers.bind<celestia::ast::AssignmentExpressionNode>(&Resolver::assignment);

  handlers.bind<celestia::ast::CallExpressionNode>(&Resolver::function_call);
  handlers.bind<celestia::ast::MemberAccessExpressionNode>(&Resolver::member_access);
  handlers.bind<celestia::ast::IndexAccessExpressionNode>(&Resolver::index_access);

  handlers.bind<celestia::ast::IdentifierExpressionNode>(&Resolver::identifier);

  handlers.bind<celestia::ast::IfStatement>(&Resolver::if_statement);
  handlers.bind<celestia::ast::WhileStatement>(&Resolver::while_statement);
  handlers.bind<celestia::ast::BlockStatement>(&Resolver::block);
  handlers.bind<celestia::ast::ExpressionStatement>(&Resolver::expression_statement);
  handlers.bind<celestia::ast::ReturnStatement>(&Resolver::return_statement);

  handlers.bind<celestia::ast::VariableDeclarationNode>(&Resolver::variable_declaration);
  handlers.bind<celestia::ast::FunctionDeclarationNode>(&Resolver::function_declaration);
  handlers.bind<celestia::ast::ModuleDeclaration>(&Resolver::module_declaration);
  handlers.bind<celestia::ast::ImportDeclarationNode>(&Resolver::import_declaration);

  handlers.bind<celestia::ast::ArrayLiteralNode>(&Resolver::array_literal);
  handlers.bind<celestia::ast::ObjectLiteralNode>(&Resolver::object_literal);

  handlers.bind<celestia::ast::TypeNode>(&Resolver::type_node);
}

void Resolver::resolve(celestia::ast::Node *node) {

  auto *root = context.unit.ast.get_root();

  if (!node || node->flags.has(NodeFlags::Resolved)) return;

  node->flags.add(NodeFlags::Resolved);

  handlers.dispatch(node);
}