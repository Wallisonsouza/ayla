#pragma once

#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/core/source/Source.hpp"
#include "celestia/core/token/token_stream.hpp"
#include "celestia/diagnostic/DiagnosticContext.hpp"
#include "celestia/semantic/scope/ScopeManager.hpp"

struct CompilationUnit {

  core::source::Source &source;

  core::memory::Arena ast_arena;

  core::memory::Arena type_arena;

  ScopeManager scopes;

  diagnostic::DiagnosticContext diagnostics;

  core::token::TokenStream tokens;

  celestia::ast::ModuleDeclaration *module = nullptr;
celestia::ast::BlockStatement *script = nullptr;

  CompilationUnit(core::source::Source &source) : source(source) {}
};