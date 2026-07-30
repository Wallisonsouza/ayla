#pragma once

#include "ast/declarations/ModuleDeclarationNode.hpp"
#include "ast/statements/BlockStatementNode.hpp"
#include "core/AST.hpp"
#include "core/source/Source.hpp"
#include "core/token/token_stream.hpp"
#include "diagnostic/DiagnosticContext.hpp"
#include "semantic/scope/scope_manager.hpp"

struct CompilationUnit {

  core::source::Source &source;

  Ast ast;

  ScopeManager scopes;

  diagnostic::DiagnosticContext diagnostics;

  core::token::TokenStream tokens;

  ayla::ast::node::ModuleDeclarationNode *module = nullptr;

  ayla::ast::node::BlockStatementNode *script = nullptr;

  CompilationUnit(core::source::Source &source) : source(source) {}
};