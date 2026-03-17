#include "ast_debug.hpp"

ASTDebug::ASTDebug(std::ostream &out) : out(out), tree(out) {}

TreeLayout::TreeLayout(std::ostream &out) : out(out) {}

void TreeLayout::begin_node(bool is_last) {

  for (bool alive : ancestors_alive) { out << (alive ? "│  " : "   "); }

  out << (is_last ? "└─ " : "├─ ");

  ancestors_alive.push_back(!is_last);
}

void TreeLayout::end_node() { ancestors_alive.pop_back(); }

void ASTDebug::debug_node(const ayla::ast::AstNode *node, bool isLast) {
  using namespace ayla::ast;
  if (!node) return;

  tree.begin_node(isLast);

  switch (node->kind) {

  case NodeKind::Pattern:
  case NodeKind::IdentifierPattern:
    debug_pattern(static_cast<const PatternNode *>(node));
    break;

  case NodeKind::ObjectLiteral:
    debug_object_literal(static_cast<const ayla::ast::node::ObjectLiteralNode *>(node));
    break;

  case NodeKind::ObjectField:
    debug_object_field(static_cast<const ayla::ast::node::ObjectFieldNode *>(node));
    break;

  case NodeKind::NumberLiteral:
    debug_number_literal(static_cast<const ayla::ast::node::NumberLiteralNode *>(node));
    break;

  case NodeKind::StringLiteral:
    debug_string_literal(static_cast<const ayla::ast::node::StringLiteralNode *>(node));
    break;

  case NodeKind::BooleanLiteral:
    debug_bool_literal(static_cast<const ayla::ast::node::BoolLiteralNode *>(node));
    break;

  case NodeKind::NullLiteral:
    debug_null_literal(static_cast<const ayla::ast::node::NullLiteralNode *>(node));
    break;

  case NodeKind::IdentifierExpression:
    debug_identifier(static_cast<const ayla::ast::node::IdentifierExpressionNode *>(node));
    break;

  case NodeKind::ImportStatement:
    debug_import(static_cast<const ayla::ast::node::ImportStatementNode *>(node));
    break;

  case NodeKind::ModuleDeclaration:
    debug_module_declaration(static_cast<const ayla::ast::node::ModuleDeclarationNode *>(node));
    break;

  case NodeKind::Type:
    debug_type(static_cast<const TypeNode *>(node));
    break;

  case NodeKind::VariableDeclaration:
    debug_variable_declaration(static_cast<const node::VariableDeclarationNode *>(node));
    break;

  case NodeKind::BinaryExpression:
    debug_binary_expression(static_cast<const ayla::ast::node::BinaryExpressionNode *>(node));
    break;

  case NodeKind::CallExpression:
    debug_function_call(static_cast<const ayla::ast::node::CallExpressionNode *>(node));
    break;

  case NodeKind::ExpressionStatement:
    debug_expression_statement(static_cast<const ayla::ast::node::ExpressionStatementNode *>(node));
    break;

  case NodeKind::FunctionDeclaration:
    debug_function_declaration(static_cast<const ayla::ast::node::FunctionDeclarationNode *>(node));
    break;

  case NodeKind::MemberAccessExpression:
    debug_path_expression(static_cast<const ayla::ast::node::MemberAccessExpressionNode *>(node));
    break;

  case NodeKind::IfStatement:
    debug_if_statement(static_cast<const ayla::ast::node::IfStatementNode *>(node));
    break;

  case NodeKind::AssignmentExpression:
    debug_ASSIGN_node(static_cast<const ayla::ast::node::AssignmentExpressionNode *>(node));
    break;

  case NodeKind::BlockStatement:
    debug_block(static_cast<const ayla::ast::node::BlockStatementNode *>(node));
    break;

  case NodeKind::IndexAccessExpression:
    debug_index_acess(static_cast<const ayla::ast::node::IndexAccessExpressionNode *>(node));
    break;

  case NodeKind::ReturnStatement:
    debug_return_statement(static_cast<const ayla::ast::node::ReturnStatementNode *>(node));
    break;

  case NodeKind::ArrayLiteral:
    debug_array_literal(static_cast<const ayla::ast::node::ArrayLiteralNode *>(node));
    break;

  case NodeKind::WhileStatement:
    debug_while(static_cast<const ayla::ast::node::WhileStatementNode *>(node));
    break;

  case NodeKind::UnaryExpression:
    debug_unary_expression(static_cast<const ayla::ast::node::UnaryExpressionNode *>(node));
    break;
  default:
    out << "<error>\n";
    break;
  }

  tree.end_node();
}

void ASTDebug::dump_ast(const Ast &ast) {

  tree.ancestors_alive.clear();

  for (size_t i = 0; i < ast.size(); ++i) {
    bool is_last = (i + 1 == ast.size());
    debug_node(ast.get_nodes()[i], is_last);
  }
}

void ASTDebug::debug_labeled(const char *label, const ayla::ast::AstNode *child, bool is_last) {
  tree.begin_node(is_last);

  debug::Console::log(label_color, label);

  if (child) { debug_node(child, true); }

  tree.end_node();
}
