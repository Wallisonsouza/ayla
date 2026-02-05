#pragma once
#include <string>

namespace ayla::ast {
enum class BinaryOperation {
  Add,
  Subtract,
  Multiply,
  Divide,
  Modulo,

  And,
  Or,

  Equal,
  NotEqual,
  Less,
  LessEqual,
  Greater,
  GreaterEqual,

};

inline std::string binary_op_to_string(BinaryOperation op) {

  switch (op) {
  case BinaryOperation::Add: return "+";
  case BinaryOperation::Subtract: return "-";
  case BinaryOperation::Multiply: return "*";
  case BinaryOperation::Divide: return "/";
  case BinaryOperation::Modulo: return "%";

  case BinaryOperation::Equal: return "==";
  case BinaryOperation::NotEqual: return "!=";
  case BinaryOperation::Less: return "<";
  case BinaryOperation::LessEqual: return "<=";
  case BinaryOperation::Greater: return ">";
  case BinaryOperation::GreaterEqual: return ">=";
  }
  return "?";
}

} // namespace ayla::ast
