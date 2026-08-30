#pragma once

#include "celestia/ast/AstDispacher.hpp"
#include "celestia/ast/declarations/ImplementationDeclaration.hpp"
#include "celestia/ast/declarations/VariableDeclaration.hpp"

#include "celestia/ast/expressions/BinaryExpressionNode.hpp"
#include "celestia/ast/expressions/IdentifierExpressionNode.hpp"
#include "celestia/ast/expressions/LiteralExpressionNode.hpp"

#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/ir/IR.hpp"

namespace celestia::lowering {

class LoweringContext {
public:
  ir::IRContext &ir;

  explicit LoweringContext(ir::IRContext &ir, CompilerEnvironment &env) : ir(ir), env(env) {}

  void lower(const ast::ModuleDeclaration *root) {

    for (auto &decl : root->declarations) { lower_declaration(decl); }
  }

  void lower_variable_declaration(const ast::VariableDeclaration *node);
  void lower_struct_declaration(const ast::StructDeclaration *node);
  void lower_capability_declaration(const ast::CapabilityDeclaration *node);
  void lower_impl_declaration(const ast::ImplDeclaration *node);

  void lower_declaration(const ast::Declaration *node);

  ir::ValueId lower_expression(const ast::Expression *node);

  ir::ValueId lower_number_literal(const ast::NumberLiteralNode *node);

  ir::ValueId lower_string_literal(const ast::StringLiteralNode *node);

  ir::ValueId lower_identifier(const ast::IdentifierExpressionNode *node);

  ir::ValueId lower_bool_literal(const ast::BoolLiteralNode *node);

  ir::ValueId lower_binary_expression(const ast::BinaryExpressionNode *node);

  void lower_pattern(const ast::PatternNode *node, ir::ValueId value);

  ir::TypeId lower_type(semantic::TypeId type_id);

  AstDispatcher<LoweringContext, const ast::Expression> dispatcher;

  CompilerEnvironment &env;
};

} // namespace celestia::lowering