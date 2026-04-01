#include "ayla-compilation/compilation_unit_manager.hpp"
#include "ayla-pipeline/pipeline.hpp"
#include "ayla-source/source_manager.hpp"
#include "context.hpp"

namespace ayla::compilation {
class Session {

  ayla::compilation::Context &context;
  CompilationUnitManager comp_manager;
  source::SourceManager source_manager;
  Pipeline pipeline;

public:
  Session(ayla::compilation::Context &ctx) : context(ctx) {}

  ayla::compilation::Unit &add_unity(const std::string &path) {
    auto &src = source_manager.load(path);
    return comp_manager.create(context, src);
  }

  void add_pass(std::unique_ptr<Pass> pass) { pipeline.add_pass(std::move(pass)); }

  void run_pipeline() {
    for (auto &unit : comp_manager.units) { pipeline.run(*unit); }
  }

  ayla::compilation::Unit &entry_unit() { return *comp_manager.units.front(); }
};

} // namespace ayla::compilation
