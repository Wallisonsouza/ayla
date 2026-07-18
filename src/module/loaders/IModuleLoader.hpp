#include <string_view>
#include <memory>
#include <Module.hpp>

class IModuleLoader
{
    virtual bool exists(std::string_view name) = 0;
    virtual std::shared_ptr<Module> load() = 0;

    virtual ~IModuleLoader() = default;

};
