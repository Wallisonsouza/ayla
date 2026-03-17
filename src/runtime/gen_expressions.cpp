
#include "runtime/ByteCode.hpp"
#include "runtime/Instruction.hpp"

namespace ayla::compiler {
uint8_t BytecodeGenerator::gen_identifier_expression(ast::node::IdentifierExpressionNode *node, uint8_t dst) {
  auto reg = current->locals.resolve(node->resolved_symbol_id);
  if (!reg) throw std::runtime_error("Unresolved identifier");

  if (*reg != dst) current->emit(runtime::Register::MOVE(dst, *reg));

  return dst;
}

uint8_t BytecodeGenerator::gen_binary_expression(ast::node::BinaryExpressionNode *node, uint8_t dst) {

  uint8_t mark = current->regs.mark();

  uint8_t left = gen_expressions(node->lhs, dst);

  uint8_t right = current->regs.alloc();
  right = gen_expressions(node->rhs, right);

  runtime::OpCode op;
  switch (node->op) {
  case ast::BinaryOperation::Add:
    op = runtime::OpCode::ADD;
    break;
  case ast::BinaryOperation::Subtract:
    op = runtime::OpCode::SUB;
    break;
  case ast::BinaryOperation::Multiply:
    op = runtime::OpCode::MUL;
    break;
  case ast::BinaryOperation::Divide:
    op = runtime::OpCode::DIV;
    break;
  default:
    throw std::runtime_error("Unhandled binary op");
  }

  current->emit(runtime::Register::ABC(op, dst, left, right));

  current->regs.free_to(mark);

  return dst;
}

uint8_t BytecodeGenerator::gen_member_expression(ast::node::MemberAccessExpressionNode *node, uint8_t dst) {
  uint8_t base_reg = gen_expr(node->base);

  std::string key = node->field->name;

  current->emit(runtime::Register::GET_TABLE(dst, base_reg, key));

  return dst;
}

uint8_t BytecodeGenerator::gen_index_expression(ast::node::IndexAccessExpressionNode *node, uint8_t dst) {
  uint8_t base_reg = gen_expr(node->base);

  using NK = ast::NodeKind;

  if (node->index->kind == NK::NumberLiteral) {
    auto *num = static_cast<ast::node::NumberLiteralNode *>(node->index);
    current->emit(runtime::Register::GET_ARRAY(dst, base_reg, static_cast<uint32_t>(num->value)));
  } else if (node->index->kind == NK::StringLiteral) {
    auto *str = static_cast<ast::node::StringLiteralNode *>(node->index);
    current->emit(runtime::Register::GET_TABLE(dst, base_reg, str->value));
  } else {
    // índice dinâmico → precisa de registrador temporário para calcular índice
    // uint8_t idx_reg = current->regs.alloc();
    // idx_reg = gen_expr_into(node->index, idx_reg);
    // current->emit(runtime::Register::GET_TABLE(dst, base_reg, idx_reg));
  }

  return dst;
}

} // namespace ayla::compiler