#pragma once

#include "graphics/glwrapping/ShaderProgram.h"
#include "graphics/text/Codepoint.h"

#include <memory>

namespace vngine {
namespace graphics {
namespace text {

class TypeFace {
public:
        virtual ~TypeFace() = default;

        virtual void setSize(int px) = 0;

        virtual std::unique_ptr<Glyph> generate(Codepoint c, std::shared_ptr<glwrapping::ShaderProgram> program) const = 0;

};

} // namespace text
} // namespace graphics
} // namespace vngine
