// #pragma once

// #include "IModuleProvider.hpp"
// #include "NativeModuleRegistry.hpp"

// class NativeModuleDescriptor : public IModuleDescriptor {};

// class NativeModuleProvider : public IModuleProvider {

// public:
//   NativeModuleProvider() { register_builtin_modules(); }

//   std::optional<ModuleSource> resolve(std::string_view name) override {

//     if (!registry_.find(name)) return {};

//     return ModuleSource{ModuleSourceType::Native, std::string(name), std::make_shared<NativeModuleDescriptor>()};
//   }

// private:
//   void register_builtin_modules() {
//     registry_.register_module("std.io", [] { return std::make_shared<IOModule>(); });

//     registry_.register_module("std.math", [] { return std::make_shared<MathModule>(); });
//   }

// private:
//   NativeModuleRegistry registry_;
// };