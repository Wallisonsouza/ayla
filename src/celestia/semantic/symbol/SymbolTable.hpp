#pragma once

#include "celestia/semantic/id/ids.hpp"
#include <string>
#include <string_view>
#include <unordered_map>

class SymbolTable
{
public:
    bool insert(std::string_view name, celestia::semantic::SymbolId id);

    celestia::semantic::SymbolId find(std::string_view name) const;

    bool contains(std::string_view name) const;

    bool erase(std::string_view name);

    void clear();

    std::size_t size() const;

    bool empty() const;

private:
    std::unordered_map<std::string, celestia::semantic::SymbolId> m_symbols;
};