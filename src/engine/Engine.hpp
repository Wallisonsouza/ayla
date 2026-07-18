#pragma once

#include "core/managers/source_manager.hpp"
#include "engine/compilation_unit_manager.hpp"
#include "engine/execution_unit_manager.hpp"
#include "engine/language_context.hpp"

class Engine {

  LanguageContext &context;

  SourceManager src_manager;
  CompilationUnitManager cu_manage;
  ExecutionUnitManager eu_manager;

public:
  Engine(LanguageContext &context) : context(context) {}

  ExecutionUnit *create_execution(const std::string &path) {

    auto source = src_manager.create_source(path);

    auto compilation = cu_manage.create_compilation_unit(context, *source);

    return eu_manager.create_execution_unit(*compilation);
  }
};