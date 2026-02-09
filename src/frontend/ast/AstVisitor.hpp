#pragma once

namespace ayla::ast::node {
struct VariableDeclarationNode;
struct FunctionDeclarationNode;
struct BinaryExpressionNode;
struct IdentifierExpressionNode;
struct NumberLiteralNode;
struct StringLiteralNode;
struct BoolLiteralNode;
struct ArrayLiteralNode;
struct ObjectLiteralNode;
struct MemberAccessExpressionNode;
struct IndexAccessNode;
struct BlockStatementNode;
struct IfStatementNode;
struct WhileStatementNode;
struct ReturnStatementNode;
struct AssignmentExpressionNode;
struct CallExpressionNode;
struct ObjectFieldNode;
struct NullLiteralNode;
struct ModuleDeclarationNode;
struct ImportStatementNode;
struct ExpressionStatementNode;

} // namespace ayla::ast::node

namespace ayla::ast {
struct PatternNode;
struct TypeNode;

struct AstVisitor {
  virtual void visit(node::ExpressionStatementNode *node) = 0;
  virtual void visit(TypeNode *node) = 0;
  virtual void visit(node::ImportStatementNode *node) = 0;
  virtual void visit(node::ObjectFieldNode *node) = 0;
  virtual void visit(node::NullLiteralNode *node) = 0;
  virtual void visit(node::ModuleDeclarationNode *node) = 0;
  virtual void visit(node::VariableDeclarationNode *node) = 0;
  virtual void visit(node::FunctionDeclarationNode *node) = 0;
  virtual void visit(node::BinaryExpressionNode *node) = 0;
  virtual void visit(node::IdentifierExpressionNode *node) = 0;
  virtual void visit(node::NumberLiteralNode *node) = 0;
  virtual void visit(node::StringLiteralNode *node) = 0;
  virtual void visit(node::BoolLiteralNode *node) = 0;
  virtual void visit(node::ArrayLiteralNode *node) = 0;
  virtual void visit(node::ObjectLiteralNode *node) = 0;
  virtual void visit(node::MemberAccessExpressionNode *node) = 0;
  virtual void visit(node::IndexAccessNode *node) = 0;
  virtual void visit(node::BlockStatementNode *node) = 0;
  virtual void visit(node::IfStatementNode *node) = 0;
  virtual void visit(node::WhileStatementNode *node) = 0;
  virtual void visit(node::ReturnStatementNode *node) = 0;
  virtual void visit(node::AssignmentExpressionNode *node) = 0;
  virtual void visit(node::CallExpressionNode *node) = 0;
  virtual void visit(PatternNode *node) = 0;
};

} // namespace ayla::ast
