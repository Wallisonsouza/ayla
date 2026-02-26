
#pragma once

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

#include "ast/AstNode.hpp"
#include "ast/PatternNode.hpp"
#include "ast/expressions/AssignmentExpression.hpp"
#include "ast/expressions/BinaryExpressionNode.hpp"
#include "ast/expressions/CallExpressionNode.hpp"
#include "ast/expressions/IdentifierExpressionNode.hpp"
#include "ast/expressions/IndexAcessExpressionNode.hpp"
#include "ast/expressions/LiteralExpressionNode.hpp"

#include "ast/expressions/MemberAccessExpressionNode.hpp"
#include "ast/statements/BlockStatementNode.hpp"
#include "ast/statements/ExpressionStatementNode.hpp"
#include "ast/statements/FunctionDeclarationNode.hpp"
#include "ast/statements/ImportStatementNode.hpp"
#include "ast/statements/ModuleDeclarationNode.hpp"
#include "ast/statements/ReturnStatementNodes.hpp"
#include "ast/statements/VariableDeclarationNode.hpp"

#include "runtime/Instruction.hpp"
#include "runtime/value/value.hpp"
#include "semantic/symbols/SymbolId.hpp"

#include "module.hpp"
//////////////////////////////////////////////////////
// LOCALS E SCOPE
//////////////////////////////////////////////////////

namespace ayla::compiler {

struct BytecodeGenerator {
  ModuleBuilder &module;

  FunctionBuilder main_function;
  FunctionBuilder *current;

  BytecodeGenerator(ModuleBuilder &m) : module(m), current(&main_function) {}

  void enter_scope() { current->locals.enter_scope(); }

  void leave_scope() { current->locals.leave_scope(); }

  uint8_t gen_expr(ayla::ast::AstNode *node) {

    uint8_t dst = current->regs.alloc();

    dst = gen_expressions(node, dst);

    return dst;
  }

  uint8_t gen_number_literal(ayla::ast::node::NumberLiteralNode *n, uint8_t dst);
  uint8_t gen_string_literal(ayla::ast::node::StringLiteralNode *s, uint8_t dst);
  uint8_t gen_boolean_literal(ayla::ast::node::BoolLiteralNode *b, uint8_t dst);

  uint8_t gen_array_literal(ayla::ast::node::ArrayLiteralNode *arr, uint8_t dst);
  uint8_t gen_object_literal(ayla::ast::node::ObjectLiteralNode *obj, uint8_t dst);

  uint8_t gen_binary_expression(ayla::ast::node::BinaryExpressionNode *bin, uint8_t dst);
  uint8_t gen_member_expression(ayla::ast::node::MemberAccessExpressionNode *mem, uint8_t dst);
  uint8_t gen_index_expression(ayla::ast::node::IndexAccessExpressionNode *idx, uint8_t dst);
  uint8_t gen_identifier_expression(ayla::ast::node::IdentifierExpressionNode *id, uint8_t dst);
  uint8_t gen_assignment_expression(ayla::ast::node::AssignmentExpressionNode *asg, uint8_t dst);

  uint8_t gen_expressions(ayla::ast::AstNode *node, uint8_t dst);

  void gen_variable_declaration(ayla::ast::node::VariableDeclarationNode *node);
  void gen_assignment_expression(ayla::ast::node::AssignmentExpressionNode *node);
  void gen_expression_statement(ayla::ast::node::ExpressionStatementNode *node);
  void gen_return_statement(ayla::ast::node::ReturnStatementNode *node);
  void gen_block_statement(ayla::ast::node::BlockStatementNode *node);
  void gen_function_declaration(ayla::ast::node::FunctionDeclarationNode *node);
  void gen_import_statement(ayla::ast::node::ImportStatementNode *node);
  void gen_statements(ayla::ast::AstNode *node);
  void gen_module_declaration(ast::node::ModuleDeclarationNode *node);

  template <typename T> void generate_ast(const std::vector<T *> &nodes) {
    for (auto *n : nodes) {
      if (!n) continue;
      gen_statements(static_cast<ayla::ast::AstNode *>(n));
    }
  }

  static ModuleBuilder build(const std::vector<ayla::ast::AstNode *> &nodes) {
    ModuleBuilder module;
    BytecodeGenerator gen(module);

    gen.generate_ast(nodes);

    gen.current->finalize();
    module.add_function(std::move(gen.main_function));

    return module;
  }
};
} // namespace ayla::compiler