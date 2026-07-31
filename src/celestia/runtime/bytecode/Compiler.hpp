// #include "ByteCode.hpp"
// #include "celestia/ast/expressions/BinaryExpressionNode.hpp"
// #include "celestia/ast/expressions/CallExpressionNode.hpp"
// #include "celestia/ast/expressions/LiteralExpressionNode.hpp"
// #include "celestia/ast/expressions/UnaryExpressionNode.hpp"
// #include "celestia/ast/statements/VariableDeclarationNode.hpp"
// #include <vector>

// struct Compiler {
//   std::vector<Instruction> code;

//   void compile_node(celestia::ast::AstNode *node) {
//     if (!node) return;

//     switch (node->kind) {

//     // Literais
//     case celestia::ast::NodeKind::NumberLiteral: {
//       auto n = static_cast<celestia::ast::node::NumberLiteralNode *>(node)->value;
//       code.push_back({OpCode::PUSH_NUMBER, Value::Number(n)});
//       break;
//     }
//     case celestia::ast::NodeKind::StringLiteral: {
//       auto s = static_cast<celestia::ast::node::StringLiteralNode *>(node)->value;
//       code.push_back({OpCode::PUSH_STRING, Value::String(s)});
//       break;
//     }
//     case celestia::ast::NodeKind::BooleanLiteral: {
//       auto b = static_cast<celestia::ast::node::BoolLiteralNode *>(node)->value;
//       code.push_back({OpCode::PUSH_BOOLEAN, Value::Boolean(b)});
//       break;
//     }

//     // Variáveis
//     case celestia::ast::NodeKind::Identifier: {
//       auto id = static_cast<celestia::ast::node::IdentifierExpressionNode *>(node);
//       code.push_back({OpCode::LOAD_VAR, {}, id->resolved_symbol_id});
//       break;
//     }
//     case celestia::ast::NodeKind::VariableDeclaration: {
//       auto decl = static_cast<celestia::ast::node::VariableDeclarationNode *>(node);
//       compile_node(decl->initializer);
//       auto *id_pattern = static_cast<celestia::ast::IdentifierPatternNode *>(decl->pattern);
//       code.push_back({OpCode::STORE_VAR, {}, id_pattern->symbol_id});
//       break;
//     }

//     // Operações binárias
//     case celestia::ast::NodeKind::BinaryExpression: {
//       auto bin = static_cast<celestia::ast::node::BinaryExpressionNode *>(node);
//       compile_node(bin->lhs);
//       compile_node(bin->rhs);
//       using BO = celestia::ast::BinaryOperation;
//       switch (bin->op) {
//       case BO::Add: code.push_back({OpCode::ADD}); break;
//       case BO::Subtract: code.push_back({OpCode::SUB}); break;
//       case BO::Multiply: code.push_back({OpCode::MUL}); break;
//       case BO::Divide: code.push_back({OpCode::DIV}); break;
//       case BO::Equal: code.push_back({OpCode::EQ}); break;
//       case BO::Less: code.push_back({OpCode::LT}); break;
//       case BO::LessEqual: code.push_back({OpCode::LTE}); break;
//       case BO::Greater: code.push_back({OpCode::GT}); break;
//       case BO::GreaterEqual: code.push_back({OpCode::GTE}); break;
//       }
//       break;
//     }

//     case celestia::ast::NodeKind::UnaryExpression: {
//       auto u = static_cast<celestia::ast::node::UnaryExpressionNode *>(node);
//       compile_node(u->operand);
//       if (u->op == ayla::UnaryOperation::NOT) code.push_back({OpCode::NOT});
//       break;
//     }

//     // Chamada de função
//     case celestia::ast::NodeKind::FunctionCall: {
//       auto call = static_cast<celestia::ast::node::CallExpressionNode *>(node);
//       compile_node(call->callee);
//       for (auto *arg : call->arguments) compile_node(arg);
//       code.push_back({OpCode::CALL, Value(static_cast<int>(call->arguments.size()))});
//       break;
//     }

//     // Assignment simples
//     case celestia::ast::NodeKind::Assignment: {
//       auto assign = static_cast<celestia::ast::node::AssignmentExpressionNode *>(node);
//       compile_node(assign->value);
//       if (assign->target->kind == celestia::ast::NodeKind::Identifier) {
//         auto *id = static_cast<celestia::ast::node::IdentifierExpressionNode *>(assign->target);
//         code.push_back({OpCode::STORE_VAR, {}, id->resolved_symbol_id});
//       }
//       break;
//     }

//     // TODO: if, while, return, objects, arrays, member access...
//     default: code.push_back({OpCode::NOP});
//     }
//   }
// };
