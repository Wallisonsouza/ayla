#pragma once

#include "celestia/ast/AstNode.hpp"

// Expressions
#include "celestia/ast/expressions/AssignmentExpression.hpp"
#include "celestia/ast/expressions/BinaryExpressionNode.hpp"
#include "celestia/ast/expressions/CallExpressionNode.hpp"
#include "celestia/ast/expressions/IdentifierExpressionNode.hpp"
#include "celestia/ast/expressions/IndexAcessExpressionNode.hpp"
#include "celestia/ast/expressions/LiteralExpressionNode.hpp"
#include "celestia/ast/expressions/MemberAccessExpressionNode.hpp"
#include "celestia/ast/expressions/UnaryExpressionNode.hpp"

// Statements
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/ast/statements/ExpressionStatementNode.hpp"
#include "celestia/ast/statements/IfStatementNode.hpp"
#include "celestia/ast/statements/ImportStatementNode.hpp"
#include "celestia/ast/statements/ReturnStatementNode.hpp"
#include "celestia/ast/statements/WhileStatementNode.hpp"

// Declarations
#include "celestia/ast/declarations/FunctionDeclarationNode.hpp"
#include "celestia/ast/declarations/ModuleDeclarationNode.hpp"
#include "celestia/ast/declarations/VariableDeclarationNode.hpp"

class AstDispatcher {
public:
  template <typename Visitor, typename Method> static void dispatch(celestia::ast::AstNode *node, Visitor *visitor, Method method) {
    using namespace celestia::ast;

    if (!node) return;

    switch (node->kind) {
    case NodeKind::ExpressionStatement: invoke<node::ExpressionStatementNode>(node, visitor, method); break;

    case NodeKind::Name: invoke<node::IdentifierExpressionNode>(node, visitor, method); break;

    case NodeKind::NumberLiteral: invoke<node::NumberLiteralNode>(node, visitor, method); break;

    case NodeKind::StringLiteral: invoke<node::StringLiteralNode>(node, visitor, method); break;

    case NodeKind::BooleanLiteral: invoke<node::BoolLiteralNode>(node, visitor, method); break;

    case NodeKind::ArrayLiteral: invoke<node::ArrayLiteralNode>(node, visitor, method); break;

    case NodeKind::ObjectLiteral: invoke<node::ObjectLiteralNode>(node, visitor, method); break;

    case NodeKind::VariableDeclaration: invoke<node::VariableDeclarationNode>(node, visitor, method); break;

    case NodeKind::FunctionDeclaration: invoke<node::FunctionDeclarationNode>(node, visitor, method); break;

    case NodeKind::Call: invoke<node::CallExpressionNode>(node, visitor, method); break;

    case NodeKind::BinaryExpression: invoke<node::BinaryExpressionNode>(node, visitor, method); break;

    case NodeKind::UnaryExpression: invoke<node::UnaryExpressionNode>(node, visitor, method); break;

    case NodeKind::Assignment: invoke<node::AssignmentExpressionNode>(node, visitor, method); break;

    case NodeKind::MemberAccess: invoke<node::MemberAccessExpressionNode>(node, visitor, method); break;

    case NodeKind::IndexAccess: invoke<node::IndexAccessExpressionNode>(node, visitor, method); break;

    case NodeKind::IfStatement: invoke<node::IfStatementNode>(node, visitor, method); break;

    case NodeKind::WhileStatement: invoke<node::WhileStatementNode>(node, visitor, method); break;

    case NodeKind::ReturnStatement: invoke<node::ReturnStatementNode>(node, visitor, method); break;

    case NodeKind::BlockStatement: invoke<node::BlockStatementNode>(node, visitor, method); break;

    case NodeKind::ImportDeclaration: invoke<node::ImportDeclarationNode>(node, visitor, method); break;

    case NodeKind::ModuleDeclaration: invoke<node::ModuleDeclarationNode>(node, visitor, method); break;

    case NodeKind::Pattern: invoke<celestia::ast::PatternNode>(node, visitor, method); break;

    case NodeKind::Type: invoke<celestia::ast::TypeNode>(node, visitor, method); break;

    default: break;
    }
  }

private:
  template <typename Node, typename Visitor, typename Method> static void invoke(celestia::ast::AstNode *node, Visitor *visitor, Method method) { (visitor->*method)(static_cast<Node *>(node)); }
};