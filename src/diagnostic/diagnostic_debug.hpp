// #pragma once

// #include "core/source/Source.hpp"

// #include "debug/console/color.hpp"
// #include "debug/console/console.hpp"

// #include "diagnostic/Diagnostic.hpp"
// #include "diagnostic/Theme.hpp"
// #include "diagnostic/text/LineCutter.hpp"
// #include "diagnostic/text/MarkerBuilder.hpp"

// #include <iostream>
// #include <sstream>

// namespace diagnostic {

// inline void print_diagnostic(const Diagnostic &diagnostic, const core::source::Source &source) {

//   debug::Console::log(theme::ErrorLabel, "[", diagnostic.title, "] ", theme::ErrorText, diagnostic.message);

//   if (diagnostic.labels.empty()) return;

//   LineCutter cutter;

//   MarkerBuilder marker;

//   // por enquanto renderiza o primeiro label
//   const auto &label = diagnostic.labels.front();

//   const auto &slice = label.slice;

//   debug::Console::log(theme::Arrow, "--> ", theme::LineInfo, "line ", slice.range.begin.line, " col ", slice.range.begin.column);

//   debug::Console::log(debug::Color::BrightBlack, source.path);

//   auto line_sv = source.buffer.get_line(slice.range.begin.line);

//   auto cut = cutter.cut(line_sv, slice.span);

//   std::ostringstream ln;

//   ln << slice.range.begin.line;

//   size_t ln_width = ln.str().size();

//   debug::Console::log(theme::LineNumber, ln.str(), theme::Separator, " | ", theme::ErrorText, cut.text);

//   auto underline = marker.underline(cut, slice.span);

//   debug::Console::log(theme::LineNumber, std::string(ln_width, ' '), theme::Separator, " | ", theme::ErrorText, underline);

//   auto caret = marker.caret(cut, slice.span);

//   debug::Console::log(theme::LineNumber, std::string(ln_width, ' '), theme::Separator, " | ", theme::Caret, caret, theme::Help, " ", label.message);

//   for (const auto &help : diagnostic.helps) { debug::Console::log(theme::Help, "help: ", help); }

//   for (const auto &note : diagnostic.notes) { debug::Console::log(theme::Help, "note: ", note); }

//   std::cout << std::endl;
// }

// } // namespace diagnostic