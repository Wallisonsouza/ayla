#pragma once
#include "core/AST.hpp"
#include "core/node/Type.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/runtime/executor.hpp"
#include "frontend/ast/AstNode.hpp"
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
  void debug_identifier(const ayla::ast::IdentifierNode *node);
  void debug_member_access(const parser::node::MemberAccessNode *node);
  void debug_import(const parser::node::statement::ImportNode *node);
  void debug_module_declaration(const parser::node::statement::ModuleDeclarationNode *node);
  void debug_type(const ayla::ast::TypeNode *node);
  void debug_variable_declaration(const ayla::ast::PatternNode *node);
  void debug_binary_expression(const ayla::ast::node::BinaryExpressionNode *node);
  void debug_function_call(const ayla::ast::node::CallExpressionNode *node);
  void debug_expression_statement(const ayla::ast::ExpressionStatementNode *node);
  void debug_object_literal(const parser::node::ObjectLiteralNode *node);
  void debug_object_field(const parser::node::ObjectFieldNode *node);
  void debug_return_statement(const parser::node::ReturnStatementNode *node);

  void debug_function_declaration(const parser::node::FunctionDeclarationNode *node);
  void debug_index_acess(const parser::node::IndexAccessNode *node);
  void debug_array_literal(const parser::node::ASTArrayLiteralNode *node);
  void debug_path_expression(const parser::node::MemberAccessNode *node);
  void debug_if_statement(const parser::node::IfStatementNode *node);
  void debug_ASSIGN_node(const parser::node::statement::AssignmentNode *node);
  void debug_block(const parser::node::BlockStatementNode *node);
  void debug_while(const parser::node::ASTWhileStatementNode *node);
  void debug_children(const std::vector<const ayla::ast::AstNode *> &children);

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