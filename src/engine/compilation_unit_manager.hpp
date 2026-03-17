#include "ayla/source/source.hpp"
#include "engine/CompilationUnit.hpp"
#include <memory>
#include <vector>

class CompilationUnitManager {

public:
  std::vector<std::unique_ptr<CompilationUnit>> units;
  CompilationUnit &create(LanguageContext &ctx, ayla::source::Source &src) {
    auto unit = std::make_unique<CompilationUnit>(ctx, src);
    auto &ref = *unit;

    units.push_back(std::move(unit));
    return ref;
  }
};
