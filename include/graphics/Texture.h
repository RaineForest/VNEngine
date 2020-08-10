#pragma once

#include "graphics/glwrapping/GLHelper.h"
#include "graphics/ITextureLoader.h"

#include <filesystem>

namespace vngine {
namespace graphics {

class Texture {
public:
        Texture(const ITextureLoader& l);
        virtual ~Texture();

        void bind() const;

private:
        GLuint texId;
};

} // namespace graphics
} // namespace vngine
