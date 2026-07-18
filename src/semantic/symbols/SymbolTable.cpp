#include "SymbolTable.hpp"

bool SymbolTable::insert(std::string_view name, SymbolId id)
{
    return m_symbols.emplace(
        std::string(name),
        id
    ).second;
}


SymbolId SymbolTable::find(std::string_view name) const
{
    auto it = m_symbols.find(std::string(name));

    if (it == m_symbols.end())
        return SymbolId();

    return it->second;
}


bool SymbolTable::contains(std::string_view name) const
{
    return m_symbols.contains(std::string(name));
}


bool SymbolTable::erase(std::string_view name)
{
    return m_symbols.erase(std::string(name)) > 0;
}


void SymbolTable::clear()
{
    m_symbols.clear();
}


std::size_t SymbolTable::size() const
{
    return m_symbols.size();
}


bool SymbolTable::empty() const
{
    return m_symbols.empty();
}