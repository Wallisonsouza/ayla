#pragma once
#include "core/memory/SymbolId.hpp"
#include "core/node/Modifier.hpp"
#include "core/token/Location.hpp"
#include "frontend/ast/AstNode.hpp"

#include <string>
#include <vector>

#include "frontend/ast/ExpressionNode.hpp"
#include "frontend/ast/StatementNode.hpp"

namespace ayla::ast {

struct ExpressionStatementNode : StatementNode {
  ExpressionNode *expression;

  explicit ExpressionStatementNode(ExpressionNode *expr) : StatementNode(NodeKind::ExpressionStatement), expression(expr) {}
};

struct TypeDeclarationNode : StatementNode {
  std::string name;
  std::vector<std::string> type_params;

  explicit TypeDeclarationNode(std::string n, std::vector<std::string> params = {}) : StatementNode(NodeKind::TypeDeclaration), name(std::move(n)), type_params(std::move(params)) {}
};

struct IdentifierNode : ayla::ast::ExpressionNode {
  std::string name;

  explicit IdentifierNode(std::string n, const SourceSlice &slice = {}) : ExpressionNode(ayla::ast::NodeKind::Identifier), name(std::move(n)) { this->slice = slice; }
};

struct TypeNode : ayla::ast::AstNode {
  IdentifierNode *identifier;
  const std::vector<TypeNode *> generics;
  bool is_primitive = false;
  SymbolId symbol_id;

  explicit TypeNode(IdentifierNode *id, bool primitive = false) : ayla::ast::AstNode(ayla::ast::NodeKind::Type), identifier(id), is_primitive(primitive) {}

  TypeNode(IdentifierNode *id, std::vector<TypeNode *> g) : ayla::ast::AstNode(ayla::ast::NodeKind::Type), identifier(id), generics(std::move(g)) {}

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

struct PatternNode : StatementNode {
  ayla::ast::IdentifierNode *identifier;
  ayla::ast::TypeNode *type;
  ayla::ast::ExpressionNode *value;
  ayla::ast::Modifiers modifiers;
  SymbolId symbol_id;

  PatternNode(ayla::ast::IdentifierNode *n, ayla::ast::TypeNode *t, ayla::ast::ExpressionNode *v, ayla::ast::Modifiers modifiers = {})
      : StatementNode(ayla::ast::NodeKind::VariableDeclaration), identifier(n), type(t), value(v), modifiers(modifiers) {}
};

struct PatternErrorNode : PatternNode {
  PatternErrorNode(const SourceSlice &expected_slice, ayla::ast::Modifiers modifiers = {}) : PatternNode(nullptr, nullptr, nullptr, modifiers) {
    this->kind = ayla::ast::NodeKind::Error;
    this->slice = expected_slice;

    flags.set(NodeFlags::HasError);

    this->slice = expected_slice;
  }
};

} // namespace ayla::ast