#include "ByteCode.hpp"
#include "ast/expressions/LiteralExpressionNode.hpp"
#include "runtime/Instruction.hpp"

namespace ayla::compiler {
uint8_t BytecodeGenerator::gen_number_literal(ast::node::NumberLiteralNode *node, uint8_t dst) {
  uint32_t k = module.add_constant(Value::Number(node->value));
  current->emit(runtime::Register::LOADK(dst, k));
  return dst;
}

uint8_t BytecodeGenerator::gen_string_literal(ast::node::StringLiteralNode *node, uint8_t dst) {
  uint32_t k = module.add_constant(Value::String(node->value));
  current->emit(runtime::Register::LOADK(dst, k));
  return dst;
}

uint8_t BytecodeGenerator::gen_boolean_literal(ast::node::BoolLiteralNode *node, uint8_t dst) {
  uint32_t k = module.add_constant(Value::Boolean(node->value));
  current->emit(runtime::Register::LOADK(dst, k));
  return dst;
}

uint8_t BytecodeGenerator::gen_array_literal(ast::node::ArrayLiteralNode *node, uint8_t dst) {

  current->emit(runtime::Register::GEN_ARRAY(dst, node->elements.size()));

  uint8_t mark = current->regs.mark();

  for (size_t i = 0; i < node->elements.size(); ++i) {

    uint8_t elem_reg = current->regs.alloc();
    elem_reg = gen_expressions(node->elements[i], elem_reg);

    current->emit(runtime::Register::SET_ARRAY(dst, i, elem_reg));

    current->regs.free_to(mark);
  }

  return dst;
}

uint8_t BytecodeGenerator::gen_object_literal(ast::node::ObjectLiteralNode *node, uint8_t dst) {

  current->emit(runtime::Register::GEN_TABLE(dst, node->fields.size()));

  uint8_t mark = current->regs.mark();

  for (auto *field : node->fields) {

    uint8_t value_reg = current->regs.alloc();
    value_reg = gen_expressions(field->value, value_reg);

    std::string key;

    if (field->key->kind == ast::NodeKind::IdentifierExpression) {
      key = static_cast<ast::node::IdentifierExpressionNode *>(field->key)->name;
    } else if (field->key->kind == ast::NodeKind::StringLiteral) {
      key = static_cast<ast::node::StringLiteralNode *>(field->key)->value;
    } else {
      throw std::runtime_error("Chave de objeto deve ser identificador ou string literal");
    }

    current->emit(runtime::Register::SET_TABLE(dst, key, value_reg));

    current->regs.free_to(mark);
  }

  return dst;
}
} // namespace ayla::compiler