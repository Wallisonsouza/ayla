#pragma once

#include <cstdint>

namespace diagnostic {

enum class DiagnosticCode : std::uint32_t {
  None = 0,

  //-----------------------------------
  // Lexer
  //-----------------------------------

  InvalidCharacter,
  InvalidEscapeSequence,
  UnterminatedString,
  UnterminatedComment,

  //-----------------------------------
  // Parser
  //-----------------------------------
  ExpectedToken,
  UnexpectedToken,
  ExpectedIdentifier,
  ExpectedExpression,
  ExpectedType,
  ExpectedPattern,
  ExpectedSemicolon,

  //-----------------------------------
  // Resolver
  //-----------------------------------

  UndefinedSymbol,
  RedefinedSymbol,
  ShadowedSymbol,

  UnknownType,
  NotAType,
  UnknownGeneric,
  InvalidGenericArity,

  //-----------------------------------
  // Type Checker
  //-----------------------------------

  TypeMismatch,
  InvalidAssignment,
  InvalidConversion,
};

} // namespace diagnostic