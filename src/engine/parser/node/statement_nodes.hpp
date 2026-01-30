#pragma once

#include "core/node/Modifier.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include "core/node/flags.hpp"

namespace parser::node {

struct BlockStatementNode : core::ast::ASTStatementNode {
  std::vector<core::ast::ASTStatementNode *> statements;

  explicit BlockStatementNode(std::vector<core::ast::ASTStatementNode *> stmts = {}) : ASTStatementNode(core::ast::NodeKind::BlockStatement), statements(std::move(stmts)) {}
};

struct BlockStatementNodeError : BlockStatementNode {
  explicit BlockStatementNodeError() : BlockStatementNode({}) { flags.set(NodeFlags::HasError); }
};

struct ASTWhileStatementNode : core::ast::ASTStatementNode {
  core::ast::ASTExpressionNode *condition;
  BlockStatementNode *block;

  ASTWhileStatementNode(core::ast::ASTExpressionNode *cond, BlockStatementNode *block) : core::ast::ASTStatementNode(core::ast::NodeKind::WhileStatement), condition(cond), block(block) {}
};

struct IfStatementNode : core::ast::ASTStatementNode {
  core::ast::ASTExpressionNode *condition;
  BlockStatementNode *if_block;
  core::ast::ASTStatementNode *else_block;

  IfStatementNode(core::ast::ASTExpressionNode *cond, BlockStatementNode *then_b, core::ast::ASTStatementNode *else_b = nullptr)
      : core::ast::ASTStatementNode(core::ast::NodeKind::IfStatement), condition(cond), if_block(then_b), else_block(else_b) {}
};

struct IfStatementNodeError : IfStatementNode {
  IfStatementNodeError() : IfStatementNode(nullptr, nullptr, nullptr) { flags.set(NodeFlags::HasError); }
};

struct FunctionDeclarationNode : core::ast::ASTStatementNode {
  core::ast::IdentifierNode *identifier;
  std::vector<core::ast::PatternNode *> params;
  core::ast::TypeNode *return_type;
  BlockStatementNode *body;
  core::ast::Modifiers modifiers;
  SymbolId symbol_id = SIZE_MAX;

  FunctionDeclarationNode(core::ast::IdentifierNode *identifier,
                          std::vector<core::ast::PatternNode *> params,
                          core::ast::TypeNode *ret_type = nullptr,
                          BlockStatementNode *b = nullptr,
                          core::ast::Modifiers mods = {})
      : ASTStatementNode(core::ast::NodeKind::FunctionDeclaration), identifier(identifier), params(std::move(params)), return_type(ret_type), body(b), modifiers(mods) {}
};

struct FunctionErrorNode : core::ast::ASTStatementNode {
  explicit FunctionErrorNode(const SourceSlice &slice = {}) : ASTStatementNode(core::ast::NodeKind::Error) {
    this->slice = slice;

    flags.set(NodeFlags::HasError);
  }
};

struct MemberAccessNode : core::ast::ASTExpressionNode {
  core::ast::ASTExpressionNode *object;
  core::ast::ASTExpressionNode *property;

  MemberAccessNode(core::ast::ASTExpressionNode *obj, core::ast::ASTExpressionNode *prop) : ASTExpressionNode(core::ast::NodeKind::MemberAccess), object(obj), property(prop) {}
};

struct IndexAccessNode : core::ast::ASTExpressionNode {
  core::ast::ASTExpressionNode *base;  // objeto ou array
  core::ast::ASTExpressionNode *index; // índice ou expressão de acesso

  IndexAccessNode(core::ast::ASTExpressionNode *b, core::ast::ASTExpressionNode *i) : ASTExpressionNode(core::ast::NodeKind::IndexAccess), base(b), index(i) {}
};

struct FunctionCallNode : core::ast::ASTExpressionNode {
  core::ast::ASTExpressionNode *callee;
  std::vector<core::ast::ASTExpressionNode *> args;
  SymbolId symbol_id = SIZE_MAX;
  FunctionCallNode(core::ast::ASTExpressionNode *c, std::vector<core::ast::ASTExpressionNode *> a) : ASTExpressionNode(core::ast::NodeKind::FunctionCall), callee(c), args(std::move(a)) {}
};

struct ReturnStatementNode : core::ast::ASTStatementNode {
  core::ast::ASTExpressionNode *value = nullptr;

  ReturnStatementNode(core::ast::ASTExpressionNode *v) : ASTStatementNode(core::ast::NodeKind::ReturnStatement), value(v) {}
};

} // namespace parser::node