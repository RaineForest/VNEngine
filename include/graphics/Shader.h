
#pragma once

#include <GL/gl.h>
#include <string>

namespace vngine {
namespace graphics {

class Shader
{
public:
        template<GLenum ShaderType>
        Shader(std::string src);

        virtual ~Shader();

        GLuint getHandle() const;

private:
        std::string getError() const;

        std::string m_source;
        GLuint m_shaderHandle;
        GLenum m_type;
};

} // namespace graphics
} // namespace vngine
