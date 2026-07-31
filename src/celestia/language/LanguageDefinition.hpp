#pragma once

#include "celestia/core/table/PrecedenceTable.hpp"
#include "celestia/core/table/TokenTable.hpp"
#include "celestia/core/table/TypeTable.hpp"
#include "celestia/semantic/types/type.hpp"

namespace celestia {
struct LanguageDefinition {

  core::table::DescriptorTable descriptors;
  core::table::OperatorTable operators;
  core::table::TypeTable types;

  void add_infix_operator(TokenKind kind, std::string text, int precedence, core::Associativity assoc, BinaryOperation operation) {
    descriptors.add(kind, text, TokenGroup::Operator);

    operators.add_infix(kind, precedence, assoc, operation);
  }

  void add_prefix_operator(TokenKind kind, std::string text, int precedence, UnaryOperation operation) {
    descriptors.add(kind, text, TokenGroup::Operator);

    operators.add_prefix(kind, precedence, operation);
  }

  void add_postfix_operator(TokenKind kind, std::string text, int precedence, PostfixOperation operation) {
    descriptors.add(kind, text, TokenGroup::Operator);

    operators.add_postfix(kind, precedence, operation);
  }

  void add_literal(TokenKind kind, std::string text, semantic::Type *type) { descriptors.add(kind, text, TokenGroup::Literal, type); }
};

} // namespace celestia

