#include "Resolver.hpp"
#include "celestia/ast/NodeState.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"

namespace celestia::semantic {

Resolver::Resolver(ResolverContext &ctx) : context(ctx), handlers(this) {

  bind_literals();
  bind_expressions();
  bind_statements();
  bind_declarations();
  bind_types();
}

void Resolver::bind_literals() {

  handlers.bind<ast::NumberLiteralNode>(&Resolver::number_literal);

  handlers.bind<ast::StringLiteralNode>(&Resolver::string_literal);

  handlers.bind<ast::BoolLiteralNode>(&Resolver::boolean_literal);

  handlers.bind<ast::ArrayLiteralNode>(&Resolver::array_literal);

  handlers.bind<ast::ObjectLiteralNode>(&Resolver::object_literal);
}

void Resolver::bind_expressions() {

  handlers.bind<ast::BinaryExpressionNode>(&Resolver::binary_expression);

  handlers.bind<ast::UnaryExpressionNode>(&Resolver::unary_expression);

  handlers.bind<ast::AssignmentExpressionNode>(&Resolver::assignment);

  handlers.bind<ast::CallExpressionNode>(&Resolver::function_call);

  handlers.bind<ast::MemberAccessExpressionNode>(&Resolver::member_access);

  handlers.bind<ast::IndexAccessExpressionNode>(&Resolver::index_access);

  handlers.bind<ast::IdentifierExpressionNode>(&Resolver::identifier);
}


void Resolver::bind_statements() {

  handlers.bind<ast::IfStatement>(&Resolver::if_statement);

  handlers.bind<ast::WhileStatement>(&Resolver::while_statement);

  handlers.bind<ast::BlockStatement>(&Resolver::block_statement);

  handlers.bind<ast::ExpressionStatement>(&Resolver::expression_statement);

  handlers.bind<ast::ReturnStatement>(&Resolver::return_statement);
}


void Resolver::bind_declarations() {

  handlers.bind<ast::VariableDeclaration>(&Resolver::variable_declaration);

  handlers.bind<ast::FunctionDeclaration>(&Resolver::function_declaration);

  handlers.bind<ast::ModuleDeclaration>(&Resolver::module_declaration);

  handlers.bind<ast::ImportDeclaration>(&Resolver::import_declaration);

  handlers.bind<ast::CapabilityDeclaration>(&Resolver::capability_declaration);

  handlers.bind<ast::ImplDeclaration>(&Resolver::impl_declaration);

  handlers.bind<ast::FieldDeclaration>(&Resolver::field_declaration);

  handlers.bind<ast::StructDeclaration>(&Resolver::struct_declaration);
}

void Resolver::bind_types() { handlers.bind<ast::TypeNode>(&Resolver::type_node); }

void Resolver::resolve(ast::Node *node) {

  if (!node) return;

  if (node->flags.has(ast::NodeFlags::Resolved)) return;

  node->flags.add(ast::NodeFlags::Resolved);

  handlers.dispatch(node);
}

} // namespace celestia::semantic