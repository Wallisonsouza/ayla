#pragma once

#include "../Diagnostic.hpp"

namespace diagnostic {

class Renderer {

public:

    virtual ~Renderer() = default;

    virtual void render(
        const Diagnostic&) = 0;

};

}