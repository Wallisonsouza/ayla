// #pragma once
// #include "core/source/Source.hpp"
// #include "core/source/SourceBuffer.hpp"
// #include "core/source/Span.hpp"
// #include "core/token/Location.hpp"
// #include "debug/console/color.hpp"
// #include "debug/console/console.hpp"
// #include "utils/Unicode.hpp"
// #include "utils/Utf8.hpp"
// #include <cstdint>
// #include <iostream>
// #include <ostream>
// #include <sstream>
// #include <string>
// #include <string_view>

// namespace diagnostic {

// // ------------------------------------------------------------
// // 🎨 Paleta semântica
// // ------------------------------------------------------------
// using C = debug::Color;

// inline auto ERR_LABEL = C::BrightRed;
// inline auto ERR_TEXT = C::Red;

// inline auto ARROW = C::DarkRed;
// inline auto LINE_INFO = C::BrightBlue;

// inline auto LINE_NO = C::BrightBlack;
// inline auto SEP = C::BrightBlack;

// inline auto CODE_TEXT = C::White;

// inline auto TILDE = C::DarkRed;
// inline auto CARET = C::BrightRed;
// inline const debug::Color HELP_TEXT(255, 215, 120);

// // ------------------------------------------------------------
// // Estruturas auxiliares
// // ------------------------------------------------------------
// struct CutLine {
//   std::string text;
//   const char *start{};
//   const char *end{};
//   int prefix_offset{0};
// };

// // ------------------------------------------------------------
// // UTF-8 helpers
// // ------------------------------------------------------------
// inline const char *compute_display_start(const char *line_ptr,
//                                          const char *span_begin,
//                                          size_t context = 10) {
//   const char *p = span_begin;
//   size_t back = 0;

//   while (p > line_ptr && back < context) {
//     do {
//       --p;
//     } while (((*p) & 0b11000000) == 0b10000000);
//     ++back;
//   }
//   return p;
// }

// inline const char *compute_display_end(const char *line_end,
//                                        const char *span_end,
//                                        size_t context = 10) {
//   const char *p = span_end;
//   size_t forward = 0;

//   while (p < line_end && forward < context) {
//     size_t len = utils::Utf::utf8_char_len(static_cast<uint8_t>(*p));
//     p += len;
//     ++forward;
//   }
//   return p;
// }

// // ------------------------------------------------------------
// // Corte de linha com ...
// // ------------------------------------------------------------
// inline CutLine cut_line(std::string_view line, const core::source::Span &span,
//                         std::string_view cut_prefix = "...",
//                         std::string_view cut_suffix = "...") {
//   const char *line_ptr = line.data();
//   const char *line_end = line_ptr + line.size();

//   CutLine out;
//   out.start = compute_display_start(line_ptr, span.begin);
//   out.end = compute_display_end(line_end, span.end);

//   if (out.start != line_ptr) {
//     out.text += cut_prefix;
//     out.prefix_offset = static_cast<int>(cut_prefix.size());
//   }

//   out.text.append(out.start, out.end);

//   if (out.end != line_end)
//     out.text += cut_suffix;

//   return out;
// }

// inline bool is_multiline(const SourceSlice &slice) {
//   return slice.range.begin.line != slice.range.end.line;
// }

// // ------------------------------------------------------------
// // Ponteiros (~, ^, path genérico)
// // ------------------------------------------------------------
// inline std::string fill_line(const char *display_start, const char *display_end,
//                              const char *span_begin, const char *span_end,
//                              int prefix_offset, std::string_view fill = " ",
//                              std::string_view mark = "~") {
//   std::string out;
//   const char *p = display_start;

//   while (p < display_end) {
//     size_t len = utils::Utf::utf8_char_len(static_cast<uint8_t>(*p));
//     char32_t cp = utils::Utf::utf8_to_codepoint(p, len);
//     int w = utils::Unicode::char_width(cp);

//     if (p >= span_begin && p < span_end) {
//       for (int i = 0; i < w; ++i)
//         out += mark;
//     } else {
//       for (int i = 0; i < w; ++i)
//         out += fill;
//     }

//     p += len;
//   }

//   return std::string(prefix_offset, ' ') + out;
// }

// // ------------------------------------------------------------
// // Diagnóstico principal
// // ------------------------------------------------------------
// inline void print_diagnostic(const std::string &title, std::string &message,
//                              const std::string &help, const SourceSlice &slice,
//                              const core::source::Source &source) {
//   constexpr std::string_view CUT = "...";

//   // Cabeçalho do erro
//   debug::Console::log(ERR_LABEL, "[", title, "] ", ERR_TEXT, message);

//   // Linha de localização
//   debug::Console::log(ARROW, "--> ", LINE_INFO, "line ", LINE_INFO,
//                       std::to_string(slice.range.begin.line), LINE_INFO,
//                       " col ", LINE_INFO,
//                       std::to_string(slice.range.begin.column), LINE_INFO, "..",
//                       LINE_INFO, std::to_string(slice.range.end.column));

//   debug::Console::log(debug::Color::BrightBlack, source.path);

//   // Linha de código cortada
//   auto line_sv = source.buffer.get_line(slice.range.begin.line);
//   auto cut = cut_line(line_sv, slice.span, CUT, CUT);

//   std::ostringstream ln;
//   ln << slice.range.begin.line;
//   size_t ln_width = ln.str().size();

//   // Imprime a linha de código
//   debug::Console::log(LINE_NO, ln.str(), SEP, " | ", CODE_TEXT, cut.text);

//   // Imprime os tildes cobrindo todo o slice
//   debug::Console::log(LINE_NO, std::string(ln_width, ' '), SEP, " | ", TILDE,
//                       fill_line(cut.start, cut.end, slice.span.begin,
//                                 slice.span.end, cut.prefix_offset));

//   // Caret no final do slice
//   int caret_pos =
//       static_cast<int>(slice.span.end - cut.start) + cut.prefix_offset - 1;
//   if (caret_pos < 0)
//     caret_pos = 0;

//   std::string caret_line(caret_pos, ' ');
//   caret_line += "^";

//   debug::Console::log(LINE_NO, std::string(ln_width, ' '), SEP, " | ", CARET,
//                       caret_line, HELP_TEXT, " help: ", help);

//   std::cout << std::endl;
// }

// } // namespace diagnostic
