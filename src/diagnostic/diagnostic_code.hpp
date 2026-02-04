#pragma once

enum class DiagnosticCode {
  UnexpectedToken,
  ExpectedToken,
  ExpectedIdentifier,
  ExpectedType,
  ExpectedExpression,
  ExpectedColon,
  ExpectedDoubleColon,
  UndeclaredSymbol,
  NotCallable,
  UnterminatedString,
  ModuleNotFound,
  RedeclaredIdentifier,
  BlockError,

  // if
  ConditionMissing,
  ConditionAssignment,
  ThenBlockMissing,
  ElseBlockMissing
};