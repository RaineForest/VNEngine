
#include "graphics/text/TextLine.h"

#include "graphics/text/Codepoint.h"

namespace vngine {
namespace graphics {
namespace text {

TextLine::TextLine(const std::string& content, const TypeFace& face, std::shared_ptr<glwrapping::ShaderProgram> program)
{
        auto codepoint = Codepoint::make(content);
        float adv = 0.0f;
        for (auto cp : codepoint) {
                std::unique_ptr<Glyph> glyph = face.generate(cp, program);
                glyph->translate(glm::vec3{adv, 0.f, 0.f});
                adv += glyph->getOffsetToNextGlyph();
                glyphs.push_back(std::move(glyph));
        }
}

void TextLine::draw(const ICamera& c) const
{
        for (auto& glyph : glyphs) {
                glyph->draw(c);
        }
}

} // namespace text
} // namespace graphics
} // namespace vngine
