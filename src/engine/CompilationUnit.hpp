#pragma once

#include "ast/declarations/ModuleDeclarationNode.hpp"
#include "ast/statements/BlockStatementNode.hpp"
#include "core/AST.hpp"
#include "core/source/Source.hpp"
#include "core/token/token_stream.hpp"

#include "diagnostic/DiagnosticContext.hpp"
#include "engine/LangContext.hpp"
#include "semantic/scope/scope_manager.hpp"

struct CompilationUnit {

  LanguageContext &context;
  core::source::Source &source;

  ScopeManager scopes;

  Ast ast;

  ayla::ast::node::ModuleDeclarationNode *module;
  ayla::ast::node::BlockStatementNode *script = nullptr;

  diagnostic::DiagnosticContext diags;

  core::token::TokenStream tokens;

  explicit CompilationUnit(LanguageContext &ctx, core::source::Source &src) : context(ctx), source(src) {}
};
