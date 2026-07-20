#include "engine/Pass.hpp"
#include <memory>
#include <vector>

class PhaseManager {
  std::vector<std::unique_ptr<Pass>> phases;
public:
  void add_phase(std::unique_ptr<Pass> phase) {
    phases.push_back(std::move(phase));
  }
  void run_phases(CompilationUnit &unit) {
    for (auto &phase : phases) {
       phase->run(unit);
    }
  }
};
