#include "runtime/ByteCode.hpp"

namespace ayla::compiler {

void BytecodeGenerator::gen_variable_declaration(ast::node::VariableDeclarationNode *var) {
  auto *id = static_cast<ast::IdentifierPatternNode *>(var->pattern);
  uint8_t r = current->alloc_local(id->symbol_id);
  if (var->initializer) gen_expressions(var->initializer, r);
}

void BytecodeGenerator::gen_assignment_expression(ast::node::AssignmentExpressionNode *asg) {
  auto *id = static_cast<ast::node::IdentifierExpressionNode *>(asg->target);
  auto reg = current->locals.resolve(id->resolved_symbol_id);
  if (!reg) throw std::runtime_error("Unresolved assignment");
  gen_expressions(asg->value, *reg);
}

void BytecodeGenerator::gen_expression_statement(ast::node::ExpressionStatementNode *s) { gen_expr(s->expression); }

void BytecodeGenerator::gen_return_statement(ast::node::ReturnStatementNode *r) {
  if (r->value) {
    uint8_t val = gen_expr(r->value);
    current->emit(runtime::Register::MOVE(0, val));
  }
}

void BytecodeGenerator::gen_block_statement(ast::node::BlockStatementNode *b) {
  enter_scope();
  generate_ast(b->statements);
  leave_scope();
}

void BytecodeGenerator::gen_function_declaration(ast::node::FunctionDeclarationNode *fn) {
  FunctionBuilder fn_builder;
  fn_builder.arity = fn->parameters.size();
  fn_builder.regs.reset(fn_builder.arity);

  for (size_t i = 0; i < fn->parameters.size(); ++i) {
    auto *id = static_cast<ast::IdentifierPatternNode *>(fn->parameters[i]);
    fn_builder.locals.add(id->symbol_id, (uint8_t)i);
  }

  FunctionBuilder *prev = current;
  current = &fn_builder;

  if (fn->body) { generate_ast(fn->body->statements); }

  fn_builder.finalize();
  size_t index = module.add_function(std::move(fn_builder));

  current = prev;

  uint8_t reg = current->alloc_local(fn->symbol_id);
  uint32_t k = module.add_constant(Value::Function(index, fn->parameters.size()));
  current->emit(runtime::Register::LOADK(reg, k));
}

void BytecodeGenerator::gen_import_statement(ast::node::ImportStatementNode *imp) {
  uint32_t k = module.add_constant(Value::Module(imp->resolved_module_id));
  uint8_t dst = current->alloc_local(imp->resolved_symbol_id);
  current->emit(runtime::Register::LOADK(dst, k));
}

void BytecodeGenerator::gen_module_declaration(ayla::ast::node::ModuleDeclarationNode *node) {
  //
  ModuleBuilder mo = BytecodeGenerator::build(node->body);
}
} // namespace ayla::compiler