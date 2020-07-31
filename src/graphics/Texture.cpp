
#include "graphics/Texture.h"

namespace vngine {
namespace graphics {

Texture::Texture(const std::filesystem::path& file, const ITextureLoader& l) {
        glGenTextures(1, &texId);
        bind();
        l.load(file); 
}

Texture::~Texture() {
        glDeleteTextures(1, &texId);
}

void Texture::bind() const {
        glBindTexture(GL_TEXTURE_2D, texId);
}

GLuint Texture::getId() const {
        return texId;
}

} // namespace graphics
} // namespace vngine
