// #pragma once

// #include <memory>
// #include <utility>


// #include "celestia/astWalker.hpp"
// #include "Pass.hpp"

// class PassManager {

// public:
//   template <typename TPass, typename... Args> TPass &add_pass(Args &&...args) {
//     auto pass = std::make_unique<TPass>(std::forward<Args>(args)...);

//     TPass &ref = *pass;

//     passes.push_back(std::move(pass));

//     return ref;
//   }

//   void run(const mocelestia::ast::Node *root) {
//     walker.walk(root, [this](const mocelestia::ast::Node *node) { dispatch(node); });
//   }

// private:
//   void dispatch(const mocelestia::ast::Node *node) {
//     for (auto &pass : passes) { pass->dispatch(node); }
//   }

// private:
//   AstWalker walker;

//   std::vector<std::unique_ptr<Pass>> passes;
// };
