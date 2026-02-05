#pragma once

#include "core/memory/SymbolId.hpp"
#include "core/node/Type.hpp"
#include "frontend/ast/AstNode.hpp"
#include <string>
#include <vector>

namespace parser::node {

struct ObjectFieldNode : ayla::ast::AstNode {
  ayla::ast::ExpressionNode *key;
  ayla::ast::ExpressionNode *value;

  ObjectFieldNode(ayla::ast::ExpressionNode *k, ayla::ast::ExpressionNode *v) : ayla::ast::AstNode(ayla::ast::NodeKind::ObjectField), key(k), value(v) {}
};

struct ObjectLiteralNode : ayla::ast::ExpressionNode {
  std::vector<ObjectFieldNode *> fields;

  ObjectLiteralNode(std::vector<ObjectFieldNode *> fields) : ayla::ast::ExpressionNode(ayla::ast::NodeKind::ObjectLiteral), fields(std::move(fields)) {}
};

} // namespace parser::node
