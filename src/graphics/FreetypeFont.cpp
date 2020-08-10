#include "graphics/FreetypeFont.h"

#include "graphics/glwrapping/MultiAttribBuffer.h"
#include "graphics/glwrapping/VertexArray.h"
#include "graphics/ITextureLoader.h"
#include "graphics/RawModel.h"
#include "graphics/Texture.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/gtc/type_ptr.hpp>

#include <mutex>

namespace vngine {
namespace graphics {

class FreetypeGlyphLoader : public ITextureLoader {
public:
        FreetypeGlyphLoader(FT_Face& f) : face(f) {} 
        virtual ~FreetypeGlyphLoader() = default;

        virtual void load() const {
                // TODO: reset to previous value
                GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
                GL_CHECK(glTexImage2D(
                        GL_TEXTURE_2D,
                        0,
                        GL_RED,
                        face->glyph->bitmap.width,
                        face->glyph->bitmap.rows,
                        0,
                        GL_RED,
                        GL_UNSIGNED_BYTE,
                        face->glyph->bitmap.buffer));
                GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
                GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
                GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
                GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
                GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
        }

private:
        FT_Face& face;
};

class CharacterModel : public IModel {
public:
        CharacterModel(FT_Face& f, std::shared_ptr<Texture> t, std::shared_ptr<glwrapping::ShaderProgram> program)
                : tex(t), shader(program)
        {
                auto verts = generateVerts(f);
                numVerts = verts.size();
                std::unique_ptr<float[]> v = std::make_unique<float[]>(uvs.size() * 5);
                for(size_t i = 0; i < uvs.size(); i++) {
                        v[i * 5 + 0] = verts[i].x;
                        v[i * 5 + 1] = verts[i].y;
                        v[i * 5 + 2] = verts[i].z;
                        v[i * 5 + 3] = uvs[i].s;
                        v[i * 5 + 4] = uvs[i].t;
                }

                arr.bind();
                buffer = std::make_unique<vngine::graphics::glwrapping::MultiAttribBuffer<float, 2>>(
                        GL_ARRAY_BUFFER,
                        std::move(v),
                        uvs.size() * 5,
                        std::array<unsigned int, 2>({3, 2}),
                        std::array<unsigned int, 2>({sizeof(float) * 5, sizeof(float) * 5}),
                        std::array<void*, 2>({0, reinterpret_cast<void*>(sizeof(float) * 3)})
                );
        }
        virtual ~CharacterModel() = default;

        virtual void draw(const ICamera& camera) const override {
                shader->setInput("vPosition", arr, *buffer, 0);
                shader->setInput("vertexUV", arr, *buffer, 1);
                shader->use();
                shader->setUniformMatrix("projection", glm::value_ptr(camera.getProjection()), 4);
                shader->setUniformMatrix("view", glm::value_ptr(camera.getView()), 4);
                shader->setUniformMatrix("model", glm::value_ptr(modelTransform), 4);
                GL_CHECK(glActiveTexture(GL_TEXTURE0));
                tex->bind();
                shader->setUniform<int>("tex", 0);
                arr.bind();
                GL_CHECK(glEnable(GL_BLEND));
                GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
                GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, numVerts));
                GL_CHECK(glDisable(GL_BLEND));
        }

private:
        std::shared_ptr<Texture> tex;
        std::shared_ptr<glwrapping::ShaderProgram> shader;
        std::unique_ptr<vngine::graphics::glwrapping::MultiAttribBuffer<float, 2>> buffer;
        vngine::graphics::glwrapping::VertexArray arr;
        unsigned int numVerts;

        static std::vector<glm::vec3> generateVerts(FT_Face& f) { 
                auto bearingX = f->glyph->bitmap_left;
                auto bearingY = f->glyph->bitmap_top;
                auto sizeX = f->glyph->bitmap.width;
                auto sizeY = f->glyph->bitmap.rows;

                return std::vector<glm::vec3>({
                        {bearingX,              bearingY + sizeY,       0.0f},
                        {bearingX,              bearingY,               0.0f},
                        {bearingX + sizeX,      bearingY,               0.0f},
                        {bearingX,              bearingY + sizeY,       0.0f},
                        {bearingX + sizeX,      bearingY,               0.0f},
                        {bearingX + sizeX,      bearingY + sizeY,       0.0f}
                });
        }
        static const std::vector<glm::vec2> uvs;
};

const std::vector<glm::vec2> CharacterModel::uvs {{
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f},
        {1.0f, 0.0f},
        {0.0f, 1.0f},
        {0.0f, 0.0f}
}};

FreetypeException::FreetypeException(int errcode) : VNgineException(std::string("Freetype Error: ") + std::string(FT_Error_String(errcode))) {}

struct FreetypeFont::FreetypeImpl {
        FT_Library lib;
        unsigned int refcount{0};
        std::mutex refMutex;
};

struct FreetypeFont::FaceImpl {
        FT_Face face{};
};

std::unique_ptr<FreetypeFont::FreetypeImpl> FreetypeFont::impl = std::make_unique<FreetypeFont::FreetypeImpl>();

FreetypeFont::FreetypeFont(const std::filesystem::path& file, int faceIndex) {
        {
                std::lock_guard<std::mutex> lock(impl->refMutex);
                if (impl->refcount == 0) {
                        FT_Error err;
                        if ((err = FT_Init_FreeType(&impl->lib))) {
                                throw FreetypeException(err);
                        }
                }
                impl->refcount++;
        }
        face = std::make_unique<FreetypeFont::FaceImpl>();
        FT_Error err;
        if ((err = FT_New_Face(impl->lib, file.c_str(), faceIndex, &face->face))) {
                FreetypeException ex(err);
                this->FreetypeFont::~FreetypeFont(); // deref explicitly to drop refcount
                throw ex;
        }
}

FreetypeFont::~FreetypeFont() {
        FT_Done_Face(face->face);
        {
                std::lock_guard<std::mutex> lock(impl->refMutex);
                impl->refcount--;
                if (impl->refcount == 0) {
                        FT_Done_FreeType(impl->lib);
                }
        }
}

void FreetypeFont::setSize(int px) {
        FT_Set_Pixel_Sizes(face->face, 0, px);
}

std::unique_ptr<IModel> FreetypeFont::generate(char c, std::shared_ptr<glwrapping::ShaderProgram> program) {
        // TODO: use the freetype cache api
        FT_Error err;
        if ((err = FT_Load_Char(face->face, c, FT_LOAD_RENDER))) {
                throw FreetypeException(err);
        }
        return std::make_unique<CharacterModel>(face->face, std::make_shared<Texture>(FreetypeGlyphLoader(face->face)), program);
}

} // namespace graphics
} // namespace vngine
