#pragma once

#include "core/module/scope.hpp"
#include "core/node/Modifier.hpp"
#include "core/node/Type.hpp"
#include "core/node/flags.hpp"

namespace parser::node {

struct BlockStatementNode : ayla::ast::ASTStatementNode {
  std::vector<ayla::ast::ASTStatementNode *> statements;

  explicit BlockStatementNode(std::vector<ayla::ast::ASTStatementNode *> stmts = {}) : ASTStatementNode(ayla::ast::NodeKind::BlockStatement), statements(std::move(stmts)) {}
};

struct BlockStatementNodeError : BlockStatementNode {
  explicit BlockStatementNodeError() : BlockStatementNode({}) { flags.set(NodeFlags::HasError); }
};

struct ASTWhileStatementNode : ayla::ast::ASTStatementNode {
  ayla::ast::ExpressionNode *condition;
  BlockStatementNode *body;

  ASTWhileStatementNode(ayla::ast::ExpressionNode *cond, BlockStatementNode *block) : ayla::ast::ASTStatementNode(ayla::ast::NodeKind::WhileStatement), condition(cond), body(block) {}
};

struct IfStatementNode : ayla::ast::ASTStatementNode {
  ayla::ast::ExpressionNode *condition;
  BlockStatementNode *then_block;
  ayla::ast::ASTStatementNode *else_block;

  IfStatementNode(ayla::ast::ExpressionNode *cond, BlockStatementNode *then_b, ayla::ast::ASTStatementNode *else_b = nullptr)
      : ayla::ast::ASTStatementNode(ayla::ast::NodeKind::IfStatement), condition(cond), then_block(then_b), else_block(else_b) {}
};

struct IfStatementNodeError : IfStatementNode {
  IfStatementNodeError() : IfStatementNode(nullptr, nullptr, nullptr) { flags.set(NodeFlags::HasError); }
};

struct FunctionDeclarationNode : ayla::ast::ASTStatementNode {
  ayla::ast::IdentifierNode *identifier;
  std::vector<ayla::ast::PatternNode *> params;
  ayla::ast::TypeNode *return_type;
  BlockStatementNode *body;
  ayla::ast::Modifiers modifiers;
  SymbolId symbol_id;
  // Value::NativeFunction *native_fn = nullptr;

  core::ParserScope *decl_scope = nullptr;

  FunctionDeclarationNode(ayla::ast::IdentifierNode *identifier,
                          std::vector<ayla::ast::PatternNode *> params,
                          ayla::ast::TypeNode *ret_type = nullptr,
                          BlockStatementNode *b = nullptr,
                          ayla::ast::Modifiers mods = {})
      : ASTStatementNode(ayla::ast::NodeKind::FunctionDeclaration), identifier(identifier), params(std::move(params)), return_type(ret_type), body(b), modifiers(mods) {}
};

struct FunctionErrorNode : ayla::ast::ASTStatementNode {
  explicit FunctionErrorNode(const SourceSlice &slice = {}) : ASTStatementNode(ayla::ast::NodeKind::Error) {
    this->slice = slice;

    flags.set(NodeFlags::HasError);
  }
};

struct MemberAccessNode : ayla::ast::ExpressionNode {
  ayla::ast::ExpressionNode *base;
  ayla::ast::IdentifierNode *field;

  MemberAccessNode(ayla::ast::ExpressionNode *b, ayla::ast::IdentifierNode *f) : ayla::ast::ExpressionNode(ayla::ast::NodeKind::MemberAccess), base(b), field(f) {}
};

struct IndexAccessNode : ayla::ast::ExpressionNode {
  ayla::ast::ExpressionNode *base;
  ayla::ast::ExpressionNode *index;

  IndexAccessNode(ayla::ast::ExpressionNode *b, ayla::ast::ExpressionNode *i) : ExpressionNode(ayla::ast::NodeKind::IndexAccess), base(b), index(i) {}
};

struct ReturnStatementNode : ayla::ast::ASTStatementNode {
  ayla::ast::ExpressionNode *value = nullptr;

  ReturnStatementNode(ayla::ast::ExpressionNode *v) : ASTStatementNode(ayla::ast::NodeKind::ReturnStatement), value(v) {}
};

} // namespace parser::node