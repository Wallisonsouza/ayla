#include "celestia/core/visitor/Stage.hpp"
#include "celestia/engine/CompilationUnit.hpp"
#include "celestia/engine/CompilerEnvironment.hpp"

class Pipeline {
public:
  template <typename T, typename... Args> T &add_stage(Args &&...args) {
    auto stage = std::make_unique<T>(std::forward<Args>(args)...);

    auto &ref = *stage;

    stages.push_back(std::move(stage));

    return ref;
  }

  void run(CompilerEnvironment &env, CompilationUnit &unit) {
    for (auto &stage : stages) stage->run(env,unit);
  }

private:
  std::vector<std::unique_ptr<Stage>> stages;
};