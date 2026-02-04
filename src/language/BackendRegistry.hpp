#pragma once
#include <memory>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

class BackendRegistry {
  std::unordered_map<std::type_index, std::shared_ptr<void>> services;

public:
  template <typename T> void set(std::shared_ptr<T> service) { services[typeid(T)] = service; }

  template <typename T> std::shared_ptr<T> get() {
    auto it = services.find(typeid(T));
    if (it == services.end()) throw std::runtime_error("Backend not registered");

    return std::static_pointer_cast<T>(it->second);
  }

  template <typename T> bool has() const { return services.count(typeid(T)) > 0; }
};
