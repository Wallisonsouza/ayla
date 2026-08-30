#pragma once

#include "celestia/diagnostic/DiagnosticCode.hpp"

#include <string_view>
#include <unordered_map>

namespace diagnostic {

struct DiagnosticMessage {
  std::string_view title;
  std::string_view text;
};

inline const std::unordered_map<DiagnosticCode, DiagnosticMessage> messages = {

    // ============================================================
    // Lexer
    // ============================================================

    {DiagnosticCode::NotAType,
     {
         .title = "not a type",
         .text = "'{name}' is not a type",
     }},

    {DiagnosticCode::InvalidCharacter,
     {
         .title = "invalid character",
         .text = "invalid character",
     }},

    {DiagnosticCode::InvalidEscapeSequence,
     {
         .title = "invalid escape sequence",
         .text = "invalid escape sequence",
     }},

    {DiagnosticCode::UnterminatedString,
     {
         .title = "unterminated string",
         .text = "unterminated string",
     }},

    {DiagnosticCode::UnterminatedComment,
     {
         .title = "unterminated comment",
         .text = "unterminated comment",
     }},

    // ============================================================
    // Parser
    // ============================================================

    {DiagnosticCode::ExpectedToken,
     {
         .title = "expected token",
         .text = "expected '{expected}', found '{found}'",
     }},
    {DiagnosticCode::UnexpectedToken,
     {
         .title = "unexpected token",
         .text = "unexpected '{found}'",
     }},

    {DiagnosticCode::ExpectedIdentifier,
     {
         .title = "expected identifier",
         .text = "expected an identifier",
     }},

    {DiagnosticCode::ExpectedExpression,
     {
         .title = "expected expression",
         .text = "expected an expression",
     }},

    {DiagnosticCode::ExpectedType,
     {
         .title = "expected type",
         .text = "expected a type",
     }},

    {DiagnosticCode::ExpectedPattern,
     {
         .title = "expected pattern",
         .text = "expected pattern , found '{found}'",
     }},

    {DiagnosticCode::ExpectedSemicolon,
     {
         .title = "expected semicolon",
         .text = "expected ';'",
     }},

    // ============================================================
    // Resolver
    // ============================================================

    {DiagnosticCode::UndefinedSymbol,
     {
         .title = "undefined symbol",
         .text = "undefined symbol '{name}'",
     }},

    {DiagnosticCode::RedefinedSymbol,
     {
         .title = "redefined symbol",
         .text = "redefinition of '{name}'",
     }},

    {DiagnosticCode::ShadowedSymbol,
     {
         .title = "shadowed symbol",
         .text = "declaration of '{name}' shadows another symbol",
     }},

    // ============================================================
    // Type Checker
    // ============================================================

    {DiagnosticCode::TypeMismatch,
     {
         .title = "type mismatch",
         .text = "type mismatch: expected {expected}, found {found}",
     }},

    {DiagnosticCode::InvalidAssignment,
     {
         .title = "invalid assignment",
         .text = "invalid assignment",
     }},

    {DiagnosticCode::InvalidConversion,
     {
         .title = "invalid conversion",
         .text = "invalid conversion",
     }},
};

} // namespace diagnostic