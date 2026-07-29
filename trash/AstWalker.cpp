// #include "AstWalker.hpp"

// // Declarations
// #include "ast/declarations/FunctionDeclarationNode.hpp"
// #include "ast/declarations/ModuleDeclarationNode.hpp"
// #include "ast/declarations/VariableDeclarationNode.hpp"

// // Expressions
// #include "ast/expressions/AssignmentExpression.hpp"
// #include "ast/expressions/BinaryExpressionNode.hpp"
// #include "ast/expressions/CallExpressionNode.hpp"
// #include "ast/expressions/IdentifierExpressionNode.hpp"
// #include "ast/expressions/IndexAcessExpressionNode.hpp"
// #include "ast/expressions/LiteralExpressionNode.hpp"
// #include "ast/expressions/MemberAccessExpressionNode.hpp"
// #include "ast/expressions/UnaryExpressionNode.hpp"

// // Statements
// #include "ast/statements/BlockStatementNode.hpp"
// #include "ast/statements/ExpressionStatementNode.hpp"
// #include "ast/statements/IfStatementNode.hpp"
// #include "ast/statements/ImportStatementNode.hpp"
// #include "ast/statements/ReturnStatementNode.hpp"
// #include "ast/statements/WhileStatementNode.hpp"

// namespace ast = ayla::ast;

// void AstWalker::walk(const ast::AstNode *node, Callback callback) {
//   if (!node) return;

//   callback(node);

//   walk_children(node, callback);
// }

// void AstWalker::walk_children(const ast::AstNode *node, Callback callback) {
//   using namespace ayla::ast;

//   switch (node->kind) {

//     // =========================
//     // Declarations
//     // =========================

//   case NodeKind::ModuleDeclaration: {
//     auto n = static_cast<const node::ModuleDeclarationNode *>(node);

//     walk(n->name, callback);

//     for (auto declaration : n->declarations) walk(declaration, callback);

//     break;
//   }

//   case NodeKind::FunctionDeclaration: {
//     auto n = static_cast<const node::FunctionDeclarationNode *>(node);

//     walk(n->name, callback);

//     for (auto parameter : n->parameters) walk(parameter, callback);

//     walk(n->return_type, callback);

//     walk(n->body, callback);

//     break;
//   }

//   case NodeKind::VariableDeclaration: {
//     auto n = static_cast<const node::VariableDeclarationNode *>(node);

//     walk(n->pattern, callback);

//     walk(n->initializer, callback);

//     break;
//   }

//     // =========================
//     // Expressions
//     // =========================

//   case NodeKind::BinaryExpression: {
//     auto n = static_cast<const node::BinaryExpressionNode *>(node);

//     walk(n->lhs, callback);

//     walk(n->rhs, callback);

//     break;
//   }

//   case NodeKind::UnaryExpression: {
//     auto n = static_cast<const node::UnaryExpressionNode *>(node);

//     walk(n->operand, callback);

//     break;
//   }

//   case NodeKind::Assignment: {
//     auto n = static_cast<const node::AssignmentExpressionNode *>(node);

//     walk(n->target, callback);

//     walk(n->value, callback);

//     break;
//   }

//   case NodeKind::Call: {
//     auto n = static_cast<const node::CallExpressionNode *>(node);

//     walk(n->callee, callback);

//     for (auto arg : n->arguments) walk(arg, callback);

//     break;
//   }

//   case NodeKind::MemberAccess: {
//     auto n = static_cast<const node::MemberAccessExpressionNode *>(node);

//     walk(n->base, callback);

//     walk(n->member, callback);

//     break;
//   }

//   case NodeKind::IndexAccess: {
//     auto n = static_cast<const node::IndexAccessExpressionNode *>(node);

//     walk(n->base, callback);

//     walk(n->index, callback);

//     break;
//   }

//   case NodeKind::IdentifierExpression: {
//     auto n = static_cast<const node::IdentifierExpressionNode *>(node);

//     walk(n->name, callback);

//     break;
//   }

//     // =========================
//     // Literals
//     // =========================

//   case NodeKind::ArrayLiteral: {
//     auto n = static_cast<const node::ArrayLiteralNode *>(node);

//     for (auto element : n->elements) walk(element, callback);

//     break;
//   }

//   case NodeKind::ObjectLiteral: {
//     auto n = static_cast<const node::ObjectLiteralNode *>(node);

//     for (auto field : n->fields) walk(field, callback);

//     break;
//   }

//   case NodeKind::ObjectField: {
//     auto n = static_cast<const node::ObjectFieldNode *>(node);

//     walk(n->key, callback);

//     walk(n->value, callback);

//     break;
//   }

//     // =========================
//     // Statements
//     // =========================

//   case NodeKind::BlockStatement: {
//     auto n = static_cast<const node::BlockStatementNode *>(node);

//     for (auto statement : n->statements) walk(statement, callback);

//     break;
//   }

//   case NodeKind::IfStatement: {
//     auto n = static_cast<const node::IfStatementNode *>(node);

//     walk(n->condition, callback);

//     walk(n->then_block, callback);

//     walk(n->else_block, callback);

//     break;
//   }

//   case NodeKind::WhileStatement: {
//     auto n = static_cast<const node::WhileStatementNode *>(node);

//     walk(n->condition, callback);

//     walk(n->body, callback);

//     break;
//   }

//   case NodeKind::ReturnStatement: {
//     auto n = static_cast<const node::ReturnStatementNode *>(node);

//     walk(n->value, callback);

//     break;
//   }

//   case NodeKind::ExpressionStatement: {
//     auto n = static_cast<const node::ExpressionStatementNode *>(node);

//     walk(n->expression, callback);

//     break;
//   }

//   case NodeKind::ImportDeclaration: {
//     auto n = static_cast<const node::ImportDeclarationNode *>(node);

//     walk(n->name, callback);

//     break;
//   }

//     // =========================
//     // Leaf nodes
//     // =========================

//   case NodeKind::Identifier:
//   case NodeKind::QualifiedName:
//   case NodeKind::Type:
//   case NodeKind::Pattern:
//   case NodeKind::IdentifierPattern:

//   case NodeKind::NumberLiteral:
//   case NodeKind::StringLiteral:
//   case NodeKind::BooleanLiteral:
//   case NodeKind::NullLiteral: break;

//   default: break;
//   }
// }