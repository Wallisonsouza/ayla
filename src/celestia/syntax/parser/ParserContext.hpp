#pragma once

#include "celestia/compiler/CompilationUnit.hpp"
#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/diagnostic/Diagnostic.hpp"


namespace celestia::syntax {
class ParseContext {
public:
  CompilationUnit &unit;
  CompilerEnvironment &env;

  explicit ParseContext(CompilationUnit &unit, CompilerEnvironment &e) : unit(unit), env(e) {}

  auto &tokens() { return unit.tokens; }

  auto &source() { return unit.source; }

  auto &get_ast() { return unit.ast_arena; }

  auto &operators() { return env.language.operators; }

  auto &diagnostics() { return unit.diagnostics; }

  void report_error(diagnostic::Diagnostic diag) { unit.diagnostics.report(diag); }

  void set_ast_module(ast::ModuleDeclaration *module) { unit.ast_module = module; }
  
  void set_module(ast::ModuleDeclaration *m) { unit.ast_module = m; }

  auto &descriptors() { return env.language.descriptors; }
};
} // namespace celestia::syntax