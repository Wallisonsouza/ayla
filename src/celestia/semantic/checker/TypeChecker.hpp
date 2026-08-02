// #pragma once

// #include "celestia/ast/Node.hpp"
// #include "celestia/ast/expressions/IdentifierExpressionNode.hpp"
// #include "celestia/core/token/Location.hpp"
// #include "celestia/diagnostic/DiagnosticCode.hpp"
// #include "celestia/compiler/CompilationUnit.hpp"
// #include "celestia/semantic/types/BuiltinTypes.hpp"

// #include "celestia/ast/declarations/FunctionDeclaration.hpp"
// #include "celestia/ast/declarations/ModuleDeclaration.hpp"
// #include "celestia/ast/declarations/VariableDeclaration.hpp"
// #include "celestia/ast/expressions/AssignmentExpression.hpp"
// #include "celestia/ast/expressions/BinaryExpressionNode.hpp"
// #include "celestia/ast/expressions/CallExpressionNode.hpp"
// #include "celestia/ast/expressions/IndexAcessExpressionNode.hpp"
// #include "celestia/ast/expressions/LiteralExpressionNode.hpp"
// #include "celestia/ast/expressions/MemberAccessExpressionNode.hpp"
// #include "celestia/ast/expressions/UnaryExpressionNode.hpp"
// #include "celestia/ast/statements/BlockStatementNode.hpp"
// #include "celestia/ast/statements/ExpressionStatementNode.hpp"
// #include "celestia/ast/statements/IfStatementNode.hpp"
// #include "celestia/ast/declarations/ImportDeclaration.hpp"
// #include "celestia/ast/statements/ReturnStatementNode.hpp"
// #include "celestia/ast/statements/WhileStatementNode.hpp"

// struct CheckerContext {};

// namespace ayla {
// class TypeChecker {

// public:
//   CompilationUnit &unit;

//   explicit TypeChecker(CompilationUnit &unit) : unit(unit) {}
// void check(ast::AstNode *node);

// private:
  

//   void check_identifier(ast::IdentifierExpressionNode *node);

//   void check_number_literal(ast::NumberLiteralNode *node) { node->inferred_type = &BuiltinTypes::Number; }

//   void check_string_literal(ast::StringLiteralNode *node) { node->inferred_type = &BuiltinTypes::String; }

//   void check_boolean_literal(ast::BoolLiteralNode *node) { node->inferred_type = &BuiltinTypes::Boolean; }

//   void check_array_literal(ast::ArrayLiteralNode *node);

//   void check_object_literal(ast::ObjectLiteralNode *node);

//   void check_pattern(ast::PatternNode *node);

//   void check_function_declaration(ast::FunctionDeclaration *node);
//   void check_variable_declaration(ast::VariableDeclaration *node);
//   void check_function_call(ast::CallExpressionNode *node);

//   // Expressões
//   void check_binary_expression(ast::BinaryExpressionNode *node);
//   void check_unary_expression(ast::UnaryExpressionNode *node);
//   void check_member_access(ast::MemberAccessExpressionNode *node);
//   void check_index_access(ast::IndexAccessExpressionNode *node);

//   // Controle
//   void check_if_statement(ast::IfStatementNode *node);
//   void check_while_statement(ast::WhileStatementNode *node);
//   void check_return_statement(ast::ReturnStatementNode *node);

//   void check_block(ast::BlockStatementNode *node);

//   void check_import_declaration_node(ast::ImportDeclaration *node);
//   void check_module_declaration(ast::ModuleDeclaration *node);
//   void check_assignment(ast::AssignmentExpressionNode *node);
//   void check_expression_statement(ast::ExpressionStatementNode *node);

//   void report_error(diagnostic::DiagnosticCode vode, SourceSlice slice) {};
// };
// } // namespace ayla
