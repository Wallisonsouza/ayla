// #pragma once

// #include "core/token/Location.hpp"
// #include "diagnostic/diagnostic_code.hpp"
// #include "diagnostic/diagnostic_context.hpp"
// #include <optional>
// #include <string>

// enum class DiagnosticOrigin { Lexer, Parser, Semantic, Runtime, Custom };

// enum class Severity { Info, Warning, Error, Fatal };

// struct Diagnostic {
//   DiagnosticOrigin origin;
//   DiagnosticCode code;
//   Severity severity;

//   std::optional<SourceSlice> slice;
//   DiagnosticContext context;

// public:
//   void set_expected(const std::string &expected) {

//     if (expected.empty()) {
//       return;
//     }

//     context.set("expected", expected);
//   }

//   void set_found(const std::string &found) {

//     if (found.empty()) {
//       return;
//     }

//     context.set("found", found);
//   }
// };
