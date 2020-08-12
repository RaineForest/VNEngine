#pragma once

#include "graphics/IModel.h"

namespace vngine {
namespace graphics {
namespace text {

class Glyph : public IModel {
public:
        virtual ~Glyph() = default;

        virtual float getWidth() const = 0;
        virtual float getHeight() const = 0;
        virtual float getOffsetToNextGlyph() const = 0;
};

} // namespace text
} // namespace graphics
} // namespace vngine