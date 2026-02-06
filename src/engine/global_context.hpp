#include "engine/language_context.hpp"
#include "runtime/interpreter/executor.hpp"

struct GlobalContext {

  LanguageContext &language_context;
  RuntimeScope global_scope;
  Executor executor;

  GlobalContext(LanguageContext &language_context) : language_context(language_context), executor(&global_scope) {}
};
