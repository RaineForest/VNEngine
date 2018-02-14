
#pragma once

#include <GL/glew.h>
#include <string>

namespace vngine {
namespace graphics {

class Shader
{
public:
        Shader(GLenum shaderType, std::string src);

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
