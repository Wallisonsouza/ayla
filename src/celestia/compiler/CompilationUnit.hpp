#pragma once

#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/core/source/Source.hpp"
#include "celestia/core/token/token_stream.hpp"
#include "celestia/diagnostic/DiagnosticContext.hpp"
#include "celestia/ir/IR.hpp"

struct CompilationUnit {

  core::source::Source &source;

  core::memory::Arena ast_arena;

  diagnostic::DiagnosticContext diagnostics;

  core::token::TokenStream tokens;

  celestia::ast::ModuleDeclaration *ast_module = nullptr;

  celestia::semantic::ModuleId module =  celestia::semantic::ModuleId::invalid();

  celestia::ir::IRContext ir;

  void set_ast_module(celestia::ast::ModuleDeclaration *module) { ast_module = module; }

  void set_module( celestia::semantic::ModuleId module) { this->module = module; }

  CompilationUnit(core::source::Source &source) : source(source) {}
};