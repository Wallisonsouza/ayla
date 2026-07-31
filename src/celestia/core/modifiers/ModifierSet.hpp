#pragma once

#include "Modifier.hpp"

struct ModifierSet
{
    Modifier value = Modifier::None;

    constexpr void add(Modifier modifier)
    {
        value = value | modifier;
    }

    constexpr void remove(Modifier modifier)
    {
        value = value & ~modifier;
    }

    constexpr bool has(Modifier modifier) const
    {
        return (value & modifier) != Modifier::None;
    }

    constexpr void clear()
    {
        value = Modifier::None;
    }
};