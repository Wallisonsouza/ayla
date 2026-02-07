#pragma once
#include "core/AST.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"

#include "frontend/ast/AstNode.hpp"
#include "frontend/ast/PatternNode.hpp"
#include "frontend/ast/expressions/AssignmentExpression.hpp"
#include "frontend/ast/expressions/BinaryExpressionNode.hpp"
#include "frontend/ast/expressions/CallExpressionNode.hpp"
#include "frontend/ast/expressions/IndexAcessExpressionNode.hpp"
#include "frontend/ast/expressions/LiteralExpressionNode.hpp"
#include "frontend/ast/expressions/MemberAccessExpressionNode.hpp"
#include "frontend/ast/statements/ExpressionStatementNode.hpp"
#include "frontend/ast/statements/IfStatementNode.hpp"
#include "frontend/ast/statements/ImportStatementNode.hpp"
#include "frontend/ast/statements/ModuleDeclarationNode.hpp"
#include "frontend/ast/statements/ReturnStatementNodes.hpp"
#include "frontend/ast/statements/VariableDeclarationNode.hpp"
#include "frontend/ast/statements/WhileStatementNode.hpp"
#include <string>
#include <vector>

struct TreeLayout {
  std::ostream &out;
  std::vector<bool> ancestors_alive;

  explicit TreeLayout(std::ostream &out);

  void begin_node(bool is_last);
  void end_node();
  void print_vertical_padding(size_t lines);
};

struct ASTDebug {

  struct LabeledChild {
    const char *label;
    const ayla::ast::AstNode *node;
  };

  debug::Color label_color = debug::Color::Blue;
  debug::Color header_color = debug::Color::Purple;

  void debug_labeled_children(const char *label, const std::vector<LabeledChild> &children, bool is_last) {
    tree.begin_node(is_last);
    out << label << "\n";

    for (size_t i = 0; i < children.size(); ++i) {
      const auto &child = children[i];
      bool child_is_last = (i + 1 == children.size());

      tree.begin_node(child_is_last);
      out << child.label << "\n";
      debug_node(child.node, true);
      tree.end_node();
    }

    tree.end_node();
  }

  void debug_header(const std::string &header) { debug::Console::log(header_color, header); }

  std::ostream &out;
  TreeLayout tree;

  explicit ASTDebug(std::ostream &out = std::cout);

  void dump_ast(const Ast &ast);
  void debug_labeled(const char *label, const ayla::ast::AstNode *child, bool is_last);

  void debug_node(const ayla::ast::AstNode *node, bool is_last);

  void debug_number_literal(const ayla::ast::node::NumberLiteralNode *node);
  void debug_string_literal(const ayla::ast::node::StringLiteralNode *node);
  void debug_bool_literal(const ayla::ast::node::BoolLiteralNode *node);

  void debug_null_literal(const ayla::ast::node::NullLiteralNode *node);
  void debug_identifier(const ayla::ast::node::IdentifierExpressionNode *node);
  void debug_member_access(const ayla::ast::node::MemberAccessExpressionNode *node);
  void debug_import(const ayla::ast::node::ImportStatementNode *node);
  void debug_module_declaration(const ayla::ast::node::ModuleDeclarationNode *node);
  void debug_type(const ayla::ast::TypeNode *node);
  void debug_variable_declaration(const ayla::ast::node::VariableDeclarationNode *node);
  void debug_binary_expression(const ayla::ast::node::BinaryExpressionNode *node);
  void debug_function_call(const ayla::ast::node::CallExpressionNode *node);
  void debug_expression_statement(const ayla::ast::node::ExpressionStatementNode *node);
  void debug_object_literal(const ayla::ast::node::ObjectLiteralNode *node);
  void debug_object_field(const ayla::ast::node::ObjectFieldNode *node);
  void debug_return_statement(const ayla::ast::node::ReturnStatementNode *node);

  void debug_function_declaration(const ayla::ast::node::FunctionDeclarationNode *node);
  void debug_index_acess(const ayla::ast::node::IndexAccessNode *node);
  void debug_array_literal(const ayla::ast::node::ArrayLiteralNode *node);
  void debug_path_expression(const ayla::ast::node::MemberAccessExpressionNode *node);
  void debug_if_statement(const ayla::ast::node::IfStatementNode *node);
  void debug_ASSIGN_node(const ayla::ast::node::AssignmentExpressionNode *node);
  void debug_block(const ayla::ast::node::BlockStatementNode *node);
  void debug_while(const ayla::ast::node::WhileStatementNode *node);
  void debug_children(const std::vector<const ayla::ast::AstNode *> &children);
  void debug_pattern(const ayla::ast::PatternNode *node);

  template <typename T> void debug_labeled_childrens(const std::vector<T *> &children, const std::string &label, bool is_last) {
    tree.begin_node(is_last);

    debug::Console::log(label_color, label);

    size_t count = 0;
    for (auto *c : children)
      if (c) ++count;

    size_t printed = 0;
    for (auto *c : children) {
      if (!c) continue;
      ++printed;
      bool child_is_last = (printed == count);
      debug_node(c, child_is_last);
    }

    tree.end_node();
  }
};