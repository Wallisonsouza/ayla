#pragma once

#include "celestia/core/token/Token.hpp"
#include "celestia/diagnostic/DiagnosticCode.hpp"
#include "celestia/diagnostic/Expected.hpp"
#include "celestia/diagnostic/Label.hpp"
#include "celestia/diagnostic/Severity.hpp"

#include "celestia/semantic/symbol/Symbol.hpp"
#include "celestia/semantic/types/type.hpp"

#include <string>
#include <variant>
#include <vector>

namespace diagnostic {

using DiagnosticValue = std::variant<Token *, TokenKind, ExpectedKind, celestia::semantic::Type *, Symbol *, std::string>;

struct Help {
  DiagnosticCode code;

  std::vector<DiagnosticValue> arguments;
};

struct Note {
  DiagnosticCode code;

  std::vector<DiagnosticValue> arguments;
};

enum class DiagnosticArgumentKind { Expected, Found, Previous, Type, Symbol, Name };

struct DiagnosticArgument {
  DiagnosticArgumentKind kind;
  DiagnosticValue value;
};

struct Diagnostic {
  Severity severity;
  DiagnosticCode code;

  std::vector<DiagnosticArgument> arguments;

  std::vector<Label> labels;
  std::vector<Help> helps;
  std::vector<Note> notes;
};

template <typename T> inline DiagnosticArgument make_argument(DiagnosticArgumentKind kind, T &&value) { return {kind, std::forward<T>(value)}; }

template <typename T> inline DiagnosticArgument expected(T &&value) { return make_argument(DiagnosticArgumentKind::Expected, std::forward<T>(value)); }

template <typename T> inline DiagnosticArgument found(T &&value) { return make_argument(DiagnosticArgumentKind::Found, std::forward<T>(value)); }

template <typename T> inline DiagnosticArgument previous(T &&value) { return make_argument(DiagnosticArgumentKind::Previous, std::forward<T>(value)); }

} // namespace diagnostic