#pragma once

#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/core/visitor/Stage.hpp"
#include "celestia/compiler/CompilationUnit.hpp"
#include <stdexcept>
#include <string>
#include <string_view>

class LanguageBootstrapStage : public Stage {
public:
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {

    if (!unit.ast_module) { throw std::runtime_error("LanguageBootstrapStage: missing AST module"); }

    Module *builtin = env.modules.builtin();

    if (!builtin) { throw std::runtime_error("LanguageBootstrapStage: builtin module not initialized"); }

    // Os símbolos devem ter sido declarados pela AST.
    bind_primitive(env, *builtin, "int", celestia::semantic::PrimitiveKind::Int);

    bind_primitive(env, *builtin, "uint", celestia::semantic::PrimitiveKind::UInt);

    bind_primitive(env, *builtin, "int8", celestia::semantic::PrimitiveKind::Int8);

    bind_primitive(env, *builtin, "int16", celestia::semantic::PrimitiveKind::Int16);

    bind_primitive(env, *builtin, "int32", celestia::semantic::PrimitiveKind::Int32);

    bind_primitive(env, *builtin, "int64", celestia::semantic::PrimitiveKind::Int64);

    bind_primitive(env, *builtin, "uint8", celestia::semantic::PrimitiveKind::UInt8);

    bind_primitive(env, *builtin, "uint16", celestia::semantic::PrimitiveKind::UInt16);

    bind_primitive(env, *builtin, "uint32", celestia::semantic::PrimitiveKind::UInt32);

    bind_primitive(env, *builtin, "uint64", celestia::semantic::PrimitiveKind::UInt64);

    bind_primitive(env, *builtin, "f32", celestia::semantic::PrimitiveKind::F32);

    bind_primitive(env, *builtin, "f64", celestia::semantic::PrimitiveKind::F64);

    bind_primitive(env, *builtin, "bool", celestia::semantic::PrimitiveKind::Bool);

    bind_primitive(env, *builtin, "char", celestia::semantic::PrimitiveKind::Char);

    bind_primitive(env, *builtin, "string", celestia::semantic::PrimitiveKind::String);

    bind_primitive(env, *builtin, "void", celestia::semantic::PrimitiveKind::Void);

    // // array<T>
    // bind_generic(env, *builtin, "array", 1);
  }

private:
  static SymbolId require_symbol(CompilerEnvironment &env, Module &module, std::string_view name) {

    SymbolId id = module.get_scope().symbol(name);

    if (!id.is_valid()) { throw std::runtime_error("LanguageBootstrapStage: builtin declaration not found: '" + std::string(name) + "'"); }

    auto *symbol = env.symbols.get(id);

    if (!symbol) { throw std::runtime_error("LanguageBootstrapStage: invalid symbol for builtin '" + std::string(name) + "'"); }

    return id;
  }

  static void bind_primitive(CompilerEnvironment &env, Module &module, std::string_view name, celestia::semantic::PrimitiveKind kind) {

    SymbolId id = require_symbol(env, module, name);

    TypeId type_id = env.types.get_or_create_primitive(id, kind);

    auto *symbol = env.symbols.get(id);

    symbol->type = type_id;
  }

  // static void bind_generic(CompilerEnvironment &env, Module &module, std::string_view name, size_t arity) {

  //   SymbolId id = require_symbol(env, module, name);

  //   TypeId type_id = env.types.get_or_create_generic_definition(id, arity);

  //   auto *symbol = env.symbols.get(id);

  //   symbol->type = type_id;
  // }
};