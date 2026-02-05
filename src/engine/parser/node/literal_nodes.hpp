#pragma once

#include "core/memory/SymbolId.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include "frontend/ast/AstNode.hpp"
#include <string>
#include <vector>

namespace parser::node {

struct NumberLiteralNode : core::ast::ASTExpressionNode {
  double value;

  explicit NumberLiteralNode(double v) : core::ast::ASTExpressionNode(core::ast::NodeKind::NumberLiteral), value(v) {}
};

struct StringLiteralNode : core::ast::ASTExpressionNode {
  std::string value;

  explicit StringLiteralNode(std::string v) : ASTExpressionNode(core::ast::NodeKind::StringLiteral), value(std::move(v)) {}
};

struct BoolLiteralNode : core::ast::ASTExpressionNode {
  bool value;

  explicit BoolLiteralNode(bool v) : ASTExpressionNode(core::ast::NodeKind::BooleanLiteral), value(v) {}
};

struct CharLiteralNode : core::ast::ASTExpressionNode {
  char32_t value;

  explicit CharLiteralNode(char32_t v) : ASTExpressionNode(core::ast::NodeKind::CharLiteral), value(v) {}
};

struct NullLiteralNode : core::ast::ASTExpressionNode {
  NullLiteralNode() : ASTExpressionNode(core::ast::NodeKind::NullLiteral) {}
};

template <typename T> struct ListNode : core::ast::ASTExpressionNode {
  std::vector<T *> elements;
  ListNode(core::ast::NodeKind kind, std::vector<T *> elems) : ASTExpressionNode(kind), elements(std::move(elems)) {}
};

struct ASTParameterListNode : ListNode<core::ast::PatternNode> {
  explicit ASTParameterListNode(std::vector<core::ast::PatternNode *> elems) : ListNode(core::ast::NodeKind::ParameterList, std::move(elems)) {}
};

struct ASTArrayLiteralNode : ListNode<core::ast::ASTExpressionNode> {
  explicit ASTArrayLiteralNode(std::vector<core::ast::ASTExpressionNode *> elems) : ListNode(core::ast::NodeKind::ArrayLiteral, std::move(elems)) {}
};

struct ObjectFieldNode : ayla::ast::AstNode {
  core::ast::ASTExpressionNode *key;
  core::ast::ASTExpressionNode *value;

  ObjectFieldNode(core::ast::ASTExpressionNode *k, core::ast::ASTExpressionNode *v) : ayla::ast::AstNode(core::ast::NodeKind::ObjectField), key(k), value(v) {}
};

struct ASTObjectFieldList : ListNode<ObjectFieldNode> {

  explicit ASTObjectFieldList(std::vector<ObjectFieldNode *> elems) : ListNode(core::ast::NodeKind::ObjectFieldList, std::move(elems)) {}
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

struct ObjectLiteralNode : core::ast::ASTExpressionNode {
  ASTObjectFieldList *field_list;

  ObjectLiteralNode(ASTObjectFieldList *f) : core::ast::ASTExpressionNode(core::ast::NodeKind::ObjectLiteral), field_list(f) {}
};

} // namespace parser::node
