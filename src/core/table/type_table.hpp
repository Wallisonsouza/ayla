#include "semantic/types/type.hpp"
#include <memory>
#include <unordered_map>
#include <string>

namespace core::table {
class TypeTable {
private:
    std::unordered_map<std::string, std::shared_ptr<Type>> map;

public:
    void add(const std::string &name, std::shared_ptr<Type> type) {
        map[name] = type;
    }

    // ADICIONE ESTE MÉTODO ABAIXO:
    std::shared_ptr<Type> find(const std::string &name) const {
        auto it = map.find(name);
        if (it != map.end()) {
            return it->second;
        }
        return nullptr; // Retorna ponteiro vazio caso não encontre o tipo
    }
};
}