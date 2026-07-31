// #pragma once


// #include "celestia/core/operators/BinaryOperation.hpp"
// #include "celestia/core/operators/UnaryOperation.hpp"
// #include "celestia/engine/CompilationUnit.hpp"

// #include "celestia/ast/expressions/AssignmentExpression.hpp"
// #include "celestia/ast/expressions/BinaryExpressionNode.hpp"
// #include "celestia/ast/expressions/CallExpressionNode.hpp"
// #include "celestia/ast/expressions/IndexAcessExpressionNode.hpp"
// #include "celestia/ast/expressions/LiteralExpressionNode.hpp"
// #include "celestia/ast/expressions/MemberAccessExpressionNode.hpp"
// #include "celestia/ast/expressions/UnaryExpressionNode.hpp"
// #include "celestia/ast/statements/BlockStatementNode.hpp"
// #include "celestia/ast/statements/ExpressionStatementNode.hpp"
// #include "celestia/ast/statements/FunctionDeclarationNode.hpp"
// #include "celestia/ast/statements/IfStatementNode.hpp"
// #include "celestia/ast/statements/ImportStatementNode.hpp"
// #include "celestia/ast/statements/ModuleDeclarationNode.hpp"
// #include "celestia/ast/statements/ReturnStatementNode.hpp"
// #include "celestia/ast/statements/VariableDeclarationNode.hpp"
// #include "celestia/ast/statements/WhileStatementNode.hpp"
// #include "runtime/scope/runtime_scope.hpp"

// #include <memory>
// #include <stdexcept>
// #include <vector>

// struct Executor {

//   std::shared_ptr<RuntimeScope> current_scope;

//   Executor(std::shared_ptr<RuntimeScope> scope) : current_scope(scope) {}

//   ExecResult execute_module_declaration(CompilationUnit &unit, celestia::ast::node::ModuleDeclarationNode *node) { return ExecResult::make_value(std::make_shared<Value>(Value::Void())); }

//   ExecResult execute_import_node(CompilationUnit &unit, celestia::ast::node::ImportStatementNode *node) {

//     // auto module = unit.context.module_manager.get(node->resolved_module_id);

//     // if (!module) throw std::runtime_error("Module not found");

//     // module->ensure_initialized();

//     // current_scope->set(node->resolved_symbol_id, module->module_object);

//     // return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
//   }

//   ExecResult execute_object(CompilationUnit &unit, celestia::ast::node::ObjectLiteralNode *node) {

//     auto obj_val = std::make_shared<Value>(Value::Object());
//     auto &obj = obj_val->get_object_ref();

//     for (size_t i = 0; i < node->fields.size(); ++i) {
//       auto &field = node->fields[i];

//       std::string key_str;

//       if (field->key->kind == celestia::ast::NodeKind::Identifier) {
//         auto *id = static_cast<celestia::ast::node::IdentifierExpressionNode *>(field->key);

//         key_str = id->name;

//       } else {

//         auto key_res = execute_node(unit, field->key);

//         if (!key_res.value) { throw std::runtime_error("Object key evaluated to null"); }

//         key_str = key_res.value->convert_to_string();
//       }

//       auto val_res = execute_node(unit, field->value);

//       obj.set(key_str, val_res.value);
//     }

//     return ExecResult::make_value(obj_val);
//   }

//   ExecResult execute_member_acess(CompilationUnit &unit, celestia::ast::node::MemberAccessExpressionNode *member) {

//     auto base_res = execute_node(unit, member->base);
//     auto base_val = base_res.value;

//     if (!base_val || !base_val->is_object()) { throw std::runtime_error("Invalid member access on non-object"); }

//     auto &obj = base_val->get_object_ref();

//     const std::string &field_name = member->field->name;

//     if (!obj.has(field_name)) { throw std::runtime_error("Field not found: " + field_name); }

//     return ExecResult::make_value(obj.get(field_name));
//   }

//   ExecResult execute_array(CompilationUnit &unit, celestia::ast::node::ArrayLiteralNode *node) {

//     array elements;

//     for (auto *el : node->elements) {
//       auto v = execute_node(unit, el);
//       if (v.is_return()) return v;
//       elements.push_back(v.value);
//     }

//     return ExecResult::make_value(std::make_shared<Value>(Value::Array(std::move(elements))));
//   }

//   ExecResult execute_index_access(CompilationUnit &unit, celestia::ast::node::IndexAccessNode *node) {
//     auto base = execute_node(unit, node->base).value;
//     auto index = execute_node(unit, node->index).value;

//     if (!base->is_array()) throw std::runtime_error("Index access on non-array");

//     size_t i = static_cast<size_t>(index->get_number());
//     auto &arr = base->get_array();

//     if (i >= arr.size()) return ExecResult::make_value(std::make_shared<Value>(Value::Null()));

//     return ExecResult::make_value(arr[i]);
//   }

//   ExecResult execute_node(CompilationUnit &unit, celestia::ast::AstNode *node) {
//     if (!node) return ExecResult::make_value(std::make_shared<Value>(Value::Null()));

//     switch (node->kind) {

//     case celestia::ast::NodeKind::ExpressionStatement: return execute_expression_statement(unit, static_cast<celestia::ast::node::ExpressionStatementNode *>(node));

//     case celestia::ast::NodeKind::Assignment: return execute_assignment(unit, static_cast<celestia::ast::node::AssignmentExpressionNode *>(node));

//     case celestia::ast::NodeKind::Identifier: return execute_identifier(static_cast<celestia::ast::node::IdentifierExpressionNode *>(node));

//     // literals
//     case celestia::ast::NodeKind::NumberLiteral: return ExecResult::make_value(std::make_shared<Value>(Value::Number(static_cast<celestia::ast::node::NumberLiteralNode *>(node)->value)));

//     case celestia::ast::NodeKind::StringLiteral: return ExecResult::make_value(std::make_shared<Value>(Value::String(static_cast<celestia::ast::node::StringLiteralNode *>(node)->value)));

//     case celestia::ast::NodeKind::BooleanLiteral: return ExecResult::make_value(std::make_shared<Value>(Value::Boolean(static_cast<celestia::ast::node::BoolLiteralNode *>(node)->value)));

//     case celestia::ast::NodeKind::ObjectLiteral: return execute_object(unit, static_cast<celestia::ast::node::ObjectLiteralNode *>(node));

//     // exps
//     case celestia::ast::NodeKind::BinaryExpression: return execute_binary(unit, static_cast<celestia::ast::node::BinaryExpressionNode *>(node));

//     case celestia::ast::NodeKind::UnaryExpression: return execute_unary(unit, static_cast<celestia::ast::node::UnaryExpressionNode *>(node));

//     case celestia::ast::NodeKind::MemberAccess: return execute_member_acess(unit, static_cast<celestia::ast::node::MemberAccessExpressionNode *>(node));

//     case celestia::ast::NodeKind::FunctionCall: return execute_function_call(unit, static_cast<celestia::ast::node::CallExpressionNode *>(node));

//     case celestia::ast::NodeKind::VariableDeclaration: return execute_variable_declaration(unit, static_cast<celestia::ast::node::VariableDeclarationNode *>(node));

//     case celestia::ast::NodeKind::BlockStatement: return execute_block(unit, static_cast<celestia::ast::node::BlockStatementNode *>(node));

//     case celestia::ast::NodeKind::IfStatement: return execute_if(unit, static_cast<celestia::ast::node::IfStatementNode *>(node));

//     case celestia::ast::NodeKind::ArrayLiteral: return execute_array(unit, static_cast<celestia::ast::node::ArrayLiteralNode *>(node));

//     case celestia::ast::NodeKind::IndexAccess: return execute_index_access(unit, static_cast<celestia::ast::node::IndexAccessNode *>(node));

//     case celestia::ast::NodeKind::WhileStatement: return execute_while(unit, static_cast<celestia::ast::node::WhileStatementNode *>(node));

//     case celestia::ast::NodeKind::FunctionDeclaration: return execute_function_declaration(unit, static_cast<celestia::ast::node::FunctionDeclarationNode *>(node));

//     case celestia::ast::NodeKind::ReturnStatement: return execute_return(unit, static_cast<celestia::ast::node::ReturnStatementNode *>(node));

//     case celestia::ast::NodeKind::ModuleDeclaration: return execute_module_declaration(unit, static_cast<celestia::ast::node::ModuleDeclarationNode *>(node));

//     case celestia::ast::NodeKind::ImportStatement: return execute_import_node(unit, static_cast<celestia::ast::node::ImportStatementNode *>(node));

//     default: return ExecResult::make_value(std::make_shared<Value>(Value::Null()));
//     }
//   }

//   ExecResult execute_function_call(CompilationUnit &unit, celestia::ast::node::CallExpressionNode *node) {
//     auto callee = execute_node(unit, node->callee).value;

//     if (!callee) throw std::runtime_error("Null callee");

//     std::vector<std::shared_ptr<Value>> args;

//     for (auto *arg_node : node->arguments) { args.push_back(execute_node(unit, arg_node).value); }

//     if (callee->is_native_function()) {
//       std::vector<Value> raw;

//       for (auto &a : args) raw.push_back(*a);

//       auto &fn = callee->get_native();
//       return ExecResult::make_value(std::make_shared<Value>(fn(raw)));
//     }

//     if (callee->is_user_function()) {
//       auto &ufn = callee->get_user_function();
//       auto *decl = ufn.node;

//       auto local = std::make_shared<RuntimeScope>(ufn.captured_scope);

//       for (size_t i = 0; i < decl->parameters.size(); ++i) {
//         auto *param = static_cast<celestia::ast::IdentifierPatternNode *>(decl->parameters[i]);
//         if (i < args.size()) {
//           local->set(param->symbol_id, args[i]);
//         } else {
//           local->set(param->symbol_id, std::make_shared<Value>(Value::Null()));
//         }
//       }

//       Executor subExec(local);
//       auto result = subExec.execute_node(unit, decl->body);

//       if (result.is_return()) return ExecResult::make_value(result.value);

//       return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
//     }

//     throw std::runtime_error("Trying to call non-function");
//   }

//   // ===================== STATEMENTS =====================
//   ExecResult execute_expression_statement(CompilationUnit &unit, celestia::ast::node::ExpressionStatementNode *node) {
//     execute_node(unit, node->expression);
//     return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
//   }

//   ExecResult execute_block(CompilationUnit &unit, celestia::ast::node::BlockStatementNode *block) {

//     ExecResult last = ExecResult::make_value(std::make_shared<Value>(Value::Void()));

//     for (auto *stmt : block->statements) {
//       last = execute_node(unit, stmt);
//       if (last.is_return()) return last;
//     }
//     return last;
//   }

//   ExecResult execute_if(CompilationUnit &unit, celestia::ast::node::IfStatementNode *node) {
//     auto cond = execute_node(unit, node->condition);
//     if (cond.value->as_bool()) return execute_node(unit, node->then_block);

//     if (node->else_block) return execute_node(unit, node->else_block);

//     return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
//   }

//   ExecResult execute_while(CompilationUnit &unit, celestia::ast::node::WhileStatementNode *node) {

//     ExecResult last = ExecResult::make_value(std::make_shared<Value>(Value::Void()));

//     while (execute_node(unit, node->condition).value->as_bool()) {
//       last = execute_node(unit, node->body);
//       if (last.is_return()) return last;
//     }
//     return last;
//   }

//   ExecResult execute_return(CompilationUnit &unit, celestia::ast::node::ReturnStatementNode *node) {
//     if (!node->value) return ExecResult::make_return(std::make_shared<Value>(Value::Void()));

//     return ExecResult::make_return(execute_node(unit, node->value).value);
//   }

//   // ===================== BINARY =====================
//   ExecResult execute_binary(CompilationUnit &unit, celestia::ast::node::BinaryExpressionNode *node) {
//     auto lhs = execute_node(unit, node->lhs).value;
//     auto rhs = execute_node(unit, node->rhs).value;

    
//     switch (node->op) {
//     case BinaryOperation::Add: return ExecResult::make_value(std::make_shared<Value>(Value::Number(lhs->get_number() + rhs->get_number())));
//     case BinaryOperation::Subtract: return ExecResult::make_value(std::make_shared<Value>(Value::Number(lhs->get_number() - rhs->get_number())));
//     case BinaryOperation::Multiply: return ExecResult::make_value(std::make_shared<Value>(Value::Number(lhs->get_number() * rhs->get_number())));
//     case BinaryOperation::Divide: return ExecResult::make_value(std::make_shared<Value>(Value::Number(lhs->get_number() / rhs->get_number())));
//     case BinaryOperation::Equal: return ExecResult::make_value(std::make_shared<Value>(Value::Boolean(lhs->get_number() == rhs->get_number())));
//     case BinaryOperation::Less: return ExecResult::make_value(std::make_shared<Value>(Value::Boolean(lhs->get_number() < rhs->get_number())));
//     case BinaryOperation::LessEqual: return ExecResult::make_value(std::make_shared<Value>(Value::Boolean(lhs->get_number() <= rhs->get_number())));
//     case BinaryOperation::Greater: return ExecResult::make_value(std::make_shared<Value>(Value::Boolean(lhs->get_number() > rhs->get_number())));
//     case BinaryOperation::GreaterEqual: return ExecResult::make_value(std::make_shared<Value>(Value::Boolean(lhs->get_number() >= rhs->get_number())));
//     default: return ExecResult::make_value(std::make_shared<Value>(Value::Null()));
//     }
//   }

//   ExecResult execute_unary(CompilationUnit &unit, celestia::ast::node::UnaryExpressionNode *node) {

//     auto operand = execute_node(unit, node->operand).value;

//     switch (node->op) {
//     case UnaryOperation::Not: return ExecResult::make_value(std::make_shared<Value>(Value::Boolean(!operand->get_boolean())));

//     default: return ExecResult::make_value(std::make_shared<Value>(Value::Null()));
//     }
//   }

//   // ===================== VARIABLES =====================
//   ExecResult execute_identifier(celestia::ast::node::IdentifierExpressionNode *Identifier) { return ExecResult::make_value(current_scope->get(Identifier->resolved_symbol_id)); }

//   ExecResult execute_variable_declaration(CompilationUnit &unit, celestia::ast::node::VariableDeclarationNode *node) {

//     std::shared_ptr<Value> val;

//     if (node->initializer) {
//       val = execute_node(unit, node->initializer).value;
//     } else {
//       val = std::make_shared<Value>(Value::Null());
//     }

//     auto *id_pattern = static_cast<celestia::ast::IdentifierPatternNode *>(node->pattern);

//     current_scope->set(id_pattern->symbol_id, val);

//     return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
//   }

//   void set_in_scope_chain(std::shared_ptr<RuntimeScope> scope, SymbolId id, std::shared_ptr<Value> val) {
//     if (scope->values.find(id) != scope->values.end()) {
//       scope->values[id] = val;
//       return;
//     }
//     if (scope->parent) {
//       set_in_scope_chain(scope->parent, id, val);
//       return;
//     }

//     scope->values[id] = val;
//   }

//   ExecResult execute_assignment(CompilationUnit &unit, celestia::ast::node::AssignmentExpressionNode *node) {
//     auto rhs = execute_node(unit, node->value).value;

//     // a = ...
//     if (node->target->kind == celestia::ast::NodeKind::Identifier) {
//       auto *id = static_cast<celestia::ast::node::IdentifierExpressionNode *>(node->target);
//       set_in_scope_chain(current_scope, id->resolved_symbol_id, rhs);
//       return ExecResult::make_value(rhs);
//     }
//     if (node->target->kind == celestia::ast::NodeKind::MemberAccess) {
//       auto *mem = static_cast<celestia::ast::node::MemberAccessExpressionNode *>(node->target);

//       auto base = execute_node(unit, mem->base).value;

//       if (!base || !base->is_object()) throw std::runtime_error("Member assignment on non-object");

//       auto &obj = base->get_object_ref();

//       const std::string &field_name = mem->field->name;

//       obj.set(field_name, rhs);

//       return ExecResult::make_value(rhs);
//     }

//     if (node->target->kind == celestia::ast::NodeKind::IndexAccess) {
//       auto *idx = static_cast<celestia::ast::node::IndexAccessNode *>(node->target);

//       auto base = execute_node(unit, idx->base).value;
//       auto index = execute_node(unit, idx->index).value;

//       if (!base->is_array()) throw std::runtime_error("Index assignment on non-array");

//       size_t i = static_cast<size_t>(index->get_number());
//       auto &arr = base->get_array();

//       if (i >= arr.size()) throw std::runtime_error("Array index out of bounds");

//       arr[i] = rhs;
//       return ExecResult::make_value(rhs);
//     }

//     throw std::runtime_error("Invalid assignment target");
//   }

//   ExecResult execute_function_declaration(CompilationUnit &unit, celestia::ast::node::FunctionDeclarationNode *node) {

//     current_scope->set(node->symbol_id, std::make_shared<Value>(Value::User(node, current_scope)));

//     return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
//   }

//   // ===================== ENTRY =====================
//   void execute_ast(CompilationUnit &unit) {
//     if (!unit.diagns.all().empty()) return;
//     for (auto *n : unit.ast.get_nodes()) execute_node(unit, n);
//   }
// };