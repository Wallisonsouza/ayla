#pragma once
#include "core/memory/SymbolId.hpp"
#include "core/node/Modifier.hpp"
#include "core/node/NodeKind.hpp"
#include "core/token/Location.hpp"
#include "frontend/ast/AstNode.hpp"

#include <string>
#include <vector>

namespace core::ast {

struct ASTStatementNode : ayla::ast::AstNode {

  bool resolved = false;
  explicit ASTStatementNode(NodeKind k) : ayla::ast::AstNode(k) {}
};

struct ASTExpressionNode : ayla::ast::AstNode {

  SymbolId resolved_symbol_id;

  explicit ASTExpressionNode(NodeKind k) : ayla::ast::AstNode(k) {}
};

struct ExpressionStatementNode : ASTStatementNode {
  ASTExpressionNode *expression;

  explicit ExpressionStatementNode(ASTExpressionNode *expr) : ASTStatementNode(NodeKind::ExpressionStatement), expression(expr) {}
};

struct TypeDeclarationNode : ASTStatementNode {
  std::string name;
  std::vector<std::string> type_params;

  explicit TypeDeclarationNode(std::string n, std::vector<std::string> params = {}) : ASTStatementNode(NodeKind::TypeDeclaration), name(std::move(n)), type_params(std::move(params)) {}
};

struct IdentifierNode : core::ast::ASTExpressionNode {
  std::string name;

  explicit IdentifierNode(std::string n, const SourceSlice &slice = {}) : ASTExpressionNode(core::ast::NodeKind::Identifier), name(std::move(n)) { this->slice = slice; }
};

struct TypeNode : ayla::ast::AstNode {
  IdentifierNode *identifier;
  const std::vector<TypeNode *> generics;
  bool is_primitive = false;
  SymbolId symbol_id;

  explicit TypeNode(IdentifierNode *id, bool primitive = false) : ayla::ast::AstNode(core::ast::NodeKind::Type), identifier(id), is_primitive(primitive) {}

  TypeNode(IdentifierNode *id, std::vector<TypeNode *> g) : ayla::ast::AstNode(core::ast::NodeKind::Type), identifier(id), generics(std::move(g)) {}

  static bool is_same_type(TypeNode *a, TypeNode *b) {
    if (a->is_primitive && b->is_primitive) { return a->identifier->name == b->identifier->name; }

    if (a->identifier->name != b->identifier->name) return false;
    if (a->generics.size() != b->generics.size()) return false;
    for (size_t i = 0; i < a->generics.size(); i++) {
      if (!is_same_type(a->generics[i], b->generics[i])) return false;
    }
    return true;
  }
};

struct PatternNode : ASTStatementNode {
  core::ast::IdentifierNode *identifier;
  core::ast::TypeNode *type;
  core::ast::ASTExpressionNode *value;
  core::ast::Modifiers modifiers;
  SymbolId symbol_id;

  PatternNode(core::ast::IdentifierNode *n, core::ast::TypeNode *t, core::ast::ASTExpressionNode *v, core::ast::Modifiers modifiers = {})
      : ASTStatementNode(core::ast::NodeKind::VariableDeclaration), identifier(n), type(t), value(v), modifiers(modifiers) {}
};

struct PatternErrorNode : PatternNode {
  PatternErrorNode(const SourceSlice &expected_slice, core::ast::Modifiers modifiers = {}) : PatternNode(nullptr, nullptr, nullptr, modifiers) {
    this->kind = core::ast::NodeKind::Error;
    this->slice = expected_slice;

    flags.set(NodeFlags::HasError);

    this->slice = expected_slice;
  }
};

} // namespace core::ast