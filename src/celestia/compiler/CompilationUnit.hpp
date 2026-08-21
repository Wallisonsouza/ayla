#pragma once

#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/core/AST.hpp"
#include "celestia/core/source/Source.hpp"
#include "celestia/core/token/token_stream.hpp"
#include "celestia/diagnostic/DiagnosticContext.hpp"
#include "celestia/semantic/scope/ScopeManager.hpp"

struct CompilationUnit {

  core::source::Source &source;

  Ast ast;

  ScopeManager scopes;

  core::memory::Arena types;

  diagnostic::DiagnosticContext diagnostics;

  core::token::TokenStream tokens;

  celestia::ast::ModuleDeclaration *module = nullptr;

  celestia::ast::BlockStatement *script = nullptr;

  CompilationUnit(core::source::Source &source) : source(source) {}
};