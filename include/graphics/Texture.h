#pragma once

#include "graphics/glwrapping/GLHelper.h"
#include "graphics/ITextureLoader.h"

#include <filesystem>

namespace vngine {
namespace graphics {

class Texture {
public:
        Texture(const std::filesystem::path& file, const ITextureLoader& l);
        virtual ~Texture();

        void bind() const;

        GLuint getId() const;

private:
        GLuint texId;
};

} // namespace graphics
} // namespace vngine
