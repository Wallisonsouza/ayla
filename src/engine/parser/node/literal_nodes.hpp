#pragma once

#include "core/memory/SymbolId.hpp"
#include "core/node/Type.hpp"
#include "frontend/ast/AstNode.hpp"
#include <string>
#include <vector>

namespace parser::node {

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

struct ObjectLiteralNode : ayla::ast::ExpressionNode {
  ASTObjectFieldList *field_list;

  ObjectLiteralNode(ASTObjectFieldList *f) : ayla::ast::ExpressionNode(ayla::ast::NodeKind::ObjectLiteral), field_list(f) {}
};

} // namespace parser::node
