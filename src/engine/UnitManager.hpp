#pragma once
#include "engine/CompilationUnit.hpp"

class UnitManager {

public:
  std::vector<std::unique_ptr<CompilationUnit>> units;

  CompilationUnit *create_compilation_unit(LanguageContext &context, core::source::Source &source) {
 
    units.push_back(std::move(std::make_unique<CompilationUnit>(context, source)));
    return units.back().get();  

  };

};
