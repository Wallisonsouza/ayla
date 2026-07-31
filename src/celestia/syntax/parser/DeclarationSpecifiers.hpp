#pragma once

#include "celestia/core/modifiers/ModifierSet.hpp"
#include "celestia/core/modifiers/Visibility.hpp"

struct DeclarationSpecifiers
{
    Visibility visibility = Visibility::Private;
    ModifierSet modifiers;
};