#pragma once

#include "celestia/core/token/Location.hpp"
#include "celestia/core/token/TokenKind.hpp"
#include "celestia/diagnostic/DiagnosticCode.hpp"
#include "celestia/diagnostic/Expected.hpp"
#include "celestia/semantic/id/ids.hpp"

#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace diagnostic {

using DiagnosticValue = std::variant<TokenKind, ExpectedKind, celestia::semantic::TypeId, celestia::semantic::SymbolId, std::string>;

enum class DiagnosticArgumentKind { Expected, Found, Previous, Type, Symbol, Name };

enum class LabelKind { Primary, Secondary };

enum class Severity { Error, Warning, Note, Help };

struct Label {
  SourceSlice slice;

  LabelKind kind;
};
struct DiagnosticArgument {
  DiagnosticArgumentKind kind;
  DiagnosticValue value;
};

struct Help {
    DiagnosticCode code;
    std::vector<DiagnosticArgument> arguments;
};

struct Note {
    DiagnosticCode code;
    std::vector<DiagnosticArgument> arguments;
};

struct Diagnostic {
  Severity severity;
  DiagnosticCode code;

  std::vector<DiagnosticArgument> arguments;

  std::vector<Label> labels;
  std::vector<Help> helps;
  std::vector<Note> notes;
};

inline Label location(SourceSlice slice, LabelKind kind = LabelKind::Primary) {

  return {
      .slice = slice,
      .kind = kind,
  };
}

template <typename T> inline DiagnosticArgument make_argument(DiagnosticArgumentKind kind, T &&value) { return {kind, std::forward<T>(value)}; }

template <typename T> inline DiagnosticArgument expected(T &&value) { return make_argument(DiagnosticArgumentKind::Expected, std::forward<T>(value)); }

template <typename T> inline DiagnosticArgument found(T &&value) { return make_argument(DiagnosticArgumentKind::Found, std::forward<T>(value)); }

template <typename T> inline DiagnosticArgument previous(T &&value) { return make_argument(DiagnosticArgumentKind::Previous, std::forward<T>(value)); }

template <typename T> inline DiagnosticArgument type(T &&value) { return make_argument(DiagnosticArgumentKind::Type, std::forward<T>(value)); }

template <typename T> inline DiagnosticArgument symbol(T &&value) { return make_argument(DiagnosticArgumentKind::Symbol, std::forward<T>(value)); }

template <typename T> inline DiagnosticArgument name(T &&value) { return make_argument(DiagnosticArgumentKind::Name, std::forward<T>(value)); }

} // namespace diagnostic