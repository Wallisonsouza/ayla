#pragma once

#include "celestia/diagnostic/DiagnosticCode.hpp"

#include <string>
#include <unordered_map>

namespace diagnostic {

struct Message {
  std::string title;
  std::string text;
};

inline const std::unordered_map<DiagnosticCode, Message> messages = {

    {DiagnosticCode::ExpectedIdentifier, {"Syntax Error", "esperado um identificador, encontrado {found}"}},

    {DiagnosticCode::ExpectedExpression, {"Syntax Error", "esperado uma expressão, encontrado {found}"}},

    {DiagnosticCode::ExpectedType, {"Syntax Error", "esperado um tipo, encontrado {found}"}}};

} // namespace diagnostic