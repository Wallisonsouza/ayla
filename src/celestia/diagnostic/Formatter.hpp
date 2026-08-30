#pragma once

#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/diagnostic/Diagnostic.hpp"

#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>

namespace diagnostic {

class DiagnosticFormatter {

public:
  // Substitui os placeholders pela representação textual dos argumentos.
  static std::string format(std::string_view message, const std::vector<DiagnosticArgument> &arguments, const CompilerEnvironment &env) {

    std::string result(message);

    for (const auto &argument : arguments) {

      const auto placeholder = placeholder_name(argument.kind);
      const auto value = format_value(argument.value, env);

      replace(result, placeholder, value);
    }

    return result;
  }

private:
  static std::string_view placeholder_name(DiagnosticArgumentKind kind) {

    switch (kind) {

    case DiagnosticArgumentKind::Expected: return "{expected}";

    case DiagnosticArgumentKind::Found: return "{found}";

    case DiagnosticArgumentKind::Previous: return "{previous}";

    case DiagnosticArgumentKind::Type: return "{type}";

    case DiagnosticArgumentKind::Symbol: return "{symbol}";

    case DiagnosticArgumentKind::Name: return "{name}";
    }

    return "{unknown}";
  }

  static std::string format_value(const DiagnosticValue &value, const CompilerEnvironment &env) {

    return std::visit([&](const auto &value) -> std::string { return format_value_impl(value, env); }, value);
  }

  static std::string format_value_impl(TokenKind kind, const CompilerEnvironment &env) {

    auto *desc = env.language.descriptors.lookup_by_kind(kind);

    if (!desc) return "EOF";

    return desc->name;
  }

  static std::string format_value_impl(ExpectedKind kind, const CompilerEnvironment &) { return std::string(); }

  static std::string format_value_impl(celestia::semantic::TypeId id, const CompilerEnvironment &env) {

    if (!id.is_valid()) return "<invalid type>";

    const auto &type = env.types.get(id);

    return type.to_string();
  }

  static std::string format_value_impl(celestia::semantic::SymbolId id, const CompilerEnvironment &env) {

    if (!id.is_valid()) return "<invalid symbol>";

    const auto *symbol = env.symbols.get(id);

    if (!symbol) return "<invalid symbol>";

    return symbol->name;
  }

  static std::string format_value_impl(const std::string &value, const CompilerEnvironment &) { return value; }

  static void replace(std::string &text, std::string_view from, std::string_view to) {

    std::size_t pos = 0;

    while ((pos = text.find(from, pos)) != std::string::npos) {

      text.replace(pos, from.size(), to);

      pos += to.size();
    }
  }
};

} // namespace diagnostic