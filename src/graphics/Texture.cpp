
#include "graphics/Texture.h"

#include <iostream>

namespace vngine {
namespace graphics {

Texture::Texture(const ITextureLoader& l) {
        GL_CHECK(glGenTextures(1, &texId));
        bind();
        l.load(); 
}

Texture::~Texture() {
        glDeleteTextures(1, &texId);
}

void Texture::bind() const {
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, texId));
}

} // namespace graphics
} // namespace vngine
