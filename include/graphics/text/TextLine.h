#pragma once

#include "graphics/glwrapping/ShaderProgram.h"
#include "graphics/IModel.h"
#include "graphics/text/Glyph.h"
#include "graphics/text/TypeFace.h"

#include <memory>
#include <string>
#include <vector>

namespace vngine {
namespace graphics {
namespace text {

class TextLine : public IModel {
public:
        TextLine(const std::string& content, const TypeFace& face, std::shared_ptr<glwrapping::ShaderProgram> program);
        virtual ~TextLine() = default;

        virtual void draw(const ICamera& c) const override;

private:
        std::vector<std::unique_ptr<Glyph>> glyphs;
};

} // namespace text
} // namespace graphics
} // namespace vngine
