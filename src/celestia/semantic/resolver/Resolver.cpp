#include "Resolver.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include <iostream>

namespace celestia::semantic {

Resolver::Resolver(ResolverContext &ctx) : context(ctx), dispatcher(this) {

  bind_literals();
  bind_expressions();
  bind_statements();
  bind_declarations();
  bind_types();
}

void Resolver::bind_literals() {

  // dispacher.bind<ast::NumberLiteralNode>(&Resolver::number_literal);

  // dispacher.bind<ast::StringLiteralNode>(&Resolver::string_literal);

  // dispacher.bind<ast::BoolLiteralNode>(&Resolver::boolean_literal);

  dispatcher.bind<ast::ArrayLiteralNode>(&Resolver::array_literal);

  dispatcher.bind<ast::ObjectLiteralNode>(&Resolver::object_literal);
}

void Resolver::bind_expressions() {

  dispatcher.bind<ast::BinaryExpressionNode>(&Resolver::binary_expression);

  dispatcher.bind<ast::UnaryExpressionNode>(&Resolver::unary_expression);

  dispatcher.bind<ast::AssignmentExpressionNode>(&Resolver::assignment);

  dispatcher.bind<ast::CallExpressionNode>(&Resolver::function_call);

  dispatcher.bind<ast::MemberAccessExpressionNode>(&Resolver::member_access);

  dispatcher.bind<ast::IndexAccessExpressionNode>(&Resolver::index_access);

  dispatcher.bind<ast::IdentifierExpressionNode>(&Resolver::identifier);
}

void Resolver::bind_statements() {

  dispatcher.bind<ast::IfStatement>(&Resolver::if_statement);

  dispatcher.bind<ast::WhileStatement>(&Resolver::while_statement);

  dispatcher.bind<ast::BlockStatement>(&Resolver::block_statement);

  dispatcher.bind<ast::ExpressionStatement>(&Resolver::expression_statement);

  dispatcher.bind<ast::ReturnStatement>(&Resolver::return_statement);
}

void Resolver::bind_declarations() {

  dispatcher.bind<ast::VariableDeclaration>(&Resolver::variable_declaration);

  dispatcher.bind<ast::FunctionDeclaration>(&Resolver::function_declaration);

  dispatcher.bind<ast::ModuleDeclaration>(&Resolver::module_declaration);

  dispatcher.bind<ast::ImportDeclaration>(&Resolver::import_declaration);

  dispatcher.bind<ast::CapabilityDeclaration>(&Resolver::capability_declaration);

  dispatcher.bind<ast::ImplDeclaration>(&Resolver::impl_declaration);

  dispatcher.bind<ast::FieldDeclaration>(&Resolver::field_declaration);

  dispatcher.bind<ast::StructDeclaration>(&Resolver::struct_declaration);
}

void Resolver::bind_types() { dispatcher.bind<ast::TypeNode>(&Resolver::type_node); }

void Resolver::resolve(ast::Node *node) {

  if (!node) return;

  if (dispatcher.dispatch(node) == DispatchResult::NotHandled) { std::cerr << "Resolver: no handler for NodeKind: " << celestia::ast::node_kind_name(node->kind) << '\n'; }
}

} // namespace celestia::semantic