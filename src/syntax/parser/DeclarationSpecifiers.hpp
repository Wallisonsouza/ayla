#pragma once

#include "core/modifiers/ModifierSet.hpp"
#include "core/modifiers/Visibility.hpp"

struct DeclarationSpecifiers
{
    Visibility visibility = Visibility::Private;
    ModifierSet modifiers;
};