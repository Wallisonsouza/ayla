#pragma once

#include "celestia/ast/declarations/ModuleDeclarationNode.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/core/AST.hpp"
#include "celestia/core/source/Source.hpp"
#include "celestia/core/token/token_stream.hpp"
#include "celestia/diagnostic/DiagnosticContext.hpp"
#include "celestia/semantic/scope/scope_manager.hpp"

struct CompilationUnit {

  core::source::Source &source;

  Ast ast;

  ScopeManager scopes;

  diagnostic::DiagnosticContext diagnostics;

  core::token::TokenStream tokens;

  celestia::ast::node::ModuleDeclarationNode *module = nullptr;

  celestia::ast::node::BlockStatementNode *script = nullptr;

  CompilationUnit(core::source::Source &source) : source(source) {}
};