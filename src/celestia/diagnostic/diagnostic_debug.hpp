#pragma once

#include "celestia/compiler/CompilationUnit.hpp"
#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/core/source/Source.hpp"

#include "celestia/debug/console/color.hpp"
#include "celestia/debug/console/console.hpp"

#include "celestia/diagnostic/Diagnostic.hpp"
#include "celestia/diagnostic/DiagnosticMessages.hpp"
#include "celestia/diagnostic/Formatter.hpp"
#include "celestia/diagnostic/Theme.hpp"
#include "celestia/diagnostic/text/LineCutter.hpp"
#include "celestia/diagnostic/text/MarkerBuilder.hpp"

#include <iostream>
#include <sstream>

namespace diagnostic {

inline void print_diagnostic(const Diagnostic &diagnostic, const core::source::Source &source, const CompilerEnvironment &env) {

  auto it = messages.find(diagnostic.code);

  if (it == messages.end()) {

    std::cerr << "[Diagnostic] missing message for code: " << static_cast<std::uint32_t>(diagnostic.code) << '\n';

    return;
  }

  const auto &message = it->second;

  auto text = DiagnosticFormatter::format(message.text, diagnostic.arguments, env);

  debug::Console::log(theme::ErrorLabel, "[", message.title, "] ", theme::ErrorText, text);

  if (diagnostic.labels.empty()) return;

  LineCutter cutter;
  MarkerBuilder marker(source.buffer);

  const auto &label = diagnostic.labels.front();

  const auto &slice = label.slice;

  debug::Console::log(theme::Arrow, "--> ", theme::LineInfo, "line ", slice.begin.line, " col ", slice.begin.column);

  debug::Console::log(debug::Color::BrightBlack, source.path);

  auto cut = cutter.cut(source, slice);

  std::ostringstream ln;
  ln << slice.begin.line;

  const size_t ln_width = ln.str().size();

  debug::Console::log(theme::LineNumber, ln.str(), theme::Separator, " | ", theme::ErrorText, cut.text);

  // ------------------------------------------------------------
  // Underline
  // ------------------------------------------------------------

  auto underline = marker.underline(cut, slice.get_span());

  debug::Console::log(theme::LineNumber, std::string(ln_width, ' '), theme::Separator, " | ", theme::ErrorText, underline);

  // ------------------------------------------------------------
  // Caret
  // ------------------------------------------------------------

  auto caret = marker.caret(cut, slice.get_span());

  debug::Console::log(theme::LineNumber, std::string(ln_width, ' '), theme::Separator, " | ", theme::Caret, caret);

  // ------------------------------------------------------------
  // Helps
  // ------------------------------------------------------------

  for (const auto &help : diagnostic.helps) {

    const auto &help_message = messages.at(help.code);

    auto help_text = DiagnosticFormatter::format(help_message.text, help.arguments, env);

    debug::Console::log(theme::Help, "help: ", help_text);
  }

  std::cout << '\n';
}

} // namespace diagnostic