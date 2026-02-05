#pragma once

#include "core/memory/SymbolId.hpp"
#include "core/node/Type.hpp"
#include "frontend/ast/AstNode.hpp"
#include <string>
#include <vector>

namespace parser::node {

struct NumberLiteralNode : ayla::ast::ExpressionNode {
  double value;

  explicit NumberLiteralNode(double v) : ayla::ast::ExpressionNode(ayla::ast::NodeKind::NumberLiteral), value(v) {}
};

struct StringLiteralNode : ayla::ast::ExpressionNode {
  std::string value;

  explicit StringLiteralNode(std::string v) : ExpressionNode(ayla::ast::NodeKind::StringLiteral), value(std::move(v)) {}
};

struct BoolLiteralNode : ayla::ast::ExpressionNode {
  bool value;

  explicit BoolLiteralNode(bool v) : ExpressionNode(ayla::ast::NodeKind::BooleanLiteral), value(v) {}
};

struct CharLiteralNode : ayla::ast::ExpressionNode {
  char32_t value;

  explicit CharLiteralNode(char32_t v) : ExpressionNode(ayla::ast::NodeKind::CharLiteral), value(v) {}
};

struct NullLiteralNode : ayla::ast::ExpressionNode {
  NullLiteralNode() : ExpressionNode(ayla::ast::NodeKind::NullLiteral) {}
};

template <typename T> struct ListNode : ayla::ast::ExpressionNode {
  std::vector<T *> elements;
  ListNode(ayla::ast::NodeKind kind, std::vector<T *> elems) : ExpressionNode(kind), elements(std::move(elems)) {}
};

struct ASTParameterListNode : ListNode<ayla::ast::PatternNode> {
  explicit ASTParameterListNode(std::vector<ayla::ast::PatternNode *> elems) : ListNode(ayla::ast::NodeKind::ParameterList, std::move(elems)) {}
};

struct ASTArrayLiteralNode : ListNode<ayla::ast::ExpressionNode> {
  explicit ASTArrayLiteralNode(std::vector<ayla::ast::ExpressionNode *> elems) : ListNode(ayla::ast::NodeKind::ArrayLiteral, std::move(elems)) {}
};

struct ObjectFieldNode : ayla::ast::AstNode {
  ayla::ast::ExpressionNode *key;
  ayla::ast::ExpressionNode *value;

  ObjectFieldNode(ayla::ast::ExpressionNode *k, ayla::ast::ExpressionNode *v) : ayla::ast::AstNode(ayla::ast::NodeKind::ObjectField), key(k), value(v) {}
};

struct ASTObjectFieldList : ListNode<ObjectFieldNode> {

  explicit ASTObjectFieldList(std::vector<ObjectFieldNode *> elems) : ListNode(ayla::ast::NodeKind::ObjectFieldList, std::move(elems)) {}
};

struct MemberTable {
  std::unordered_map<std::string, SymbolId> members;

  bool add(const std::string &name, SymbolId id) {

    if (has(name)) return false;

    return members.emplace(name, id).second;
  }

  bool has(const std::string &name) const { return members.find(name) != members.end(); }

  SymbolId get(const std::string &name) const {
    auto it = members.find(name);
    if (it == members.end()) return SymbolId();
    return it->second;
  }

  bool remove(const std::string &name) { return members.erase(name) > 0; }

  void clear() { members.clear(); }

  size_t size() const { return members.size(); }

  auto begin() const { return members.begin(); }
  auto end() const { return members.end(); }
};

struct ObjectLiteralNode : ayla::ast::ExpressionNode {
  ASTObjectFieldList *field_list;

  ObjectLiteralNode(ASTObjectFieldList *f) : ayla::ast::ExpressionNode(ayla::ast::NodeKind::ObjectLiteral), field_list(f) {}
};

} // namespace parser::node
