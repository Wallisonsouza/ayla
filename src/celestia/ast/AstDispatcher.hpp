#pragma once

#include "celestia/ast/Node.hpp"

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
  template <typename Visitor, typename Method> static void dispatch(celestia::ast::Node *node, Visitor *visitor, Method method) {
    using namespace celestia::ast;

    if (!node) return;

    switch (node->kind) {
    case NodeKind::ExpressionStatement: invoke<ExpressionStatement>(node, visitor, method); break;

    case NodeKind::Name: invoke<IdentifierExpressionNode>(node, visitor, method); break;

    case NodeKind::NumberLiteral: invoke<NumberLiteralNode>(node, visitor, method); break;

    case NodeKind::StringLiteral: invoke<StringLiteralNode>(node, visitor, method); break;

    case NodeKind::BooleanLiteral: invoke<BoolLiteralNode>(node, visitor, method); break;

    case NodeKind::ArrayLiteral: invoke<ArrayLiteralNode>(node, visitor, method); break;

    case NodeKind::ObjectLiteral: invoke<ObjectLiteralNode>(node, visitor, method); break;

    case NodeKind::VariableDeclaration: invoke<VariableDeclarationNode>(node, visitor, method); break;

    case NodeKind::FunctionDeclaration: invoke<FunctionDeclarationNode>(node, visitor, method); break;

    case NodeKind::Call: invoke<CallExpressionNode>(node, visitor, method); break;

    case NodeKind::BinaryExpression: invoke<BinaryExpressionNode>(node, visitor, method); break;

    case NodeKind::UnaryExpression: invoke<UnaryExpressionNode>(node, visitor, method); break;

    case NodeKind::Assignment: invoke<AssignmentExpressionNode>(node, visitor, method); break;

    case NodeKind::MemberAccess: invoke<MemberAccessExpressionNode>(node, visitor, method); break;

    case NodeKind::IndexAccess: invoke<IndexAccessExpressionNode>(node, visitor, method); break;

    case NodeKind::IfStatement: invoke<IfStatement>(node, visitor, method); break;

    case NodeKind::WhileStatement: invoke<WhileStatement>(node, visitor, method); break;

    case NodeKind::ReturnStatement: invoke<ReturnStatement>(node, visitor, method); break;

    case NodeKind::BlockStatement: invoke<BlockStatement>(node, visitor, method); break;

    case NodeKind::ImportDeclaration: invoke<ImportDeclarationNode>(node, visitor, method); break;

    case NodeKind::ModuleDeclaration: invoke<ModuleDeclaration>(node, visitor, method); break;

    case NodeKind::Pattern: invoke<PatternNode>(node, visitor, method); break;

    case NodeKind::Type: invoke<TypeNode>(node, visitor, method); break;

    default: break;
    }
  }

private:
  template <typename Node, typename Visitor, typename Method> static void invoke(celestia::ast::Node *node, Visitor *visitor, Method method) { (visitor->*method)(static_cast<Node *>(node)); }
};