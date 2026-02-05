#include "diagnostic/formatter.hpp"
#include "diagnostic/diagnostic_debug.hpp"
#include "diagnostic/diagnostics_table.hpp"
#include <string>
#include <variant>

struct DiagnosticValueRenderer {
  const CompilationUnit &unit;

  std::string operator()(const std::string &s) const { return s; }

  std::string operator()(TokenKind k) const { return "'" + unit.context.descriptor_table.lookup_by_kind(k)->name + "'"; }

  std::string operator()(ayla::ast::NodeKind k) const { return "unit.context.node_names.at(k);"; }
};

std::string render_value(const DiagnosticValue &v, const CompilationUnit &unit) { return std::visit(DiagnosticValueRenderer{unit}, v); }

std::string apply_template(const std::string &tmpl, const DiagnosticContext &ctx, const CompilationUnit &unit) {

  std::string out;
  out.reserve(tmpl.size());

  for (size_t i = 0; i < tmpl.size();) {
    if (tmpl[i] == '{') {
      size_t end = tmpl.find('}', i + 1);
      if (end == std::string::npos) {
        out += tmpl[i++];
        continue;
      }

      auto key = tmpl.substr(i + 1, end - i - 1);

      if (auto *val = ctx.get(std::string(key))) { out += render_value(*val, unit); }

      i = end + 1;
      continue;
    }

    out += tmpl[i++];
  }

  return out;
}

void print(const Diagnostic &diag, const CompilationUnit &unit) {

  auto it = DIAG_PT_BR.find(diag.code);
  if (it == DIAG_PT_BR.end()) {
    std::cerr << "Erro desconhecido\n";
    return;
  }

  const auto &tmpl = it->second;

  // Mensagem

  std::string help = apply_template(tmpl.help, diag.context, unit);
  std::string message = apply_template(tmpl.message, diag.context, unit);

  diagnostic::print_diagnostic(tmpl.title, message, help, diag.slice.value_or({}), unit.source);
}
