#include "AylaLanguage.hpp"

#include "Operators.hpp"
#include "Tokens.hpp"
#include "Types.hpp"

namespace ayla::language {

celestia::LanguageDefinition create_definition() {
  
  celestia::LanguageDefinition definition;

  register_types(definition);
  register_operators(definition);
  register_tokens(definition);

  return definition;
}

} // namespace ayla::language