
#include "Exceptions.h"
#include "graphics/glwrapping/Shader.h"

#include <memory>

namespace vngine {
namespace graphics {
namespace glwrapping {

Shader::Shader(GLenum shaderType, std::string src) :
        m_source(src),
        m_type(shaderType)
{
        // create the handle
        m_shaderHandle = glCreateShader(shaderType);

        // attach the source to the handle
        const GLchar* psource = static_cast<const GLchar*>(m_source.c_str());
        glShaderSource(m_shaderHandle, 1, &psource, NULL);

        // compile the shader
        glCompileShader(m_shaderHandle);
        GLint flag;
        glGetShaderiv(m_shaderHandle, GL_COMPILE_STATUS, &flag);
        if (flag == GL_FALSE) {
                throw GLException("Shader Compile error: \n" + getError());
        }
}

Shader::~Shader()
{
        glDeleteShader(m_shaderHandle);
}

GLuint Shader::getHandle() const
{
        return m_shaderHandle;
}

std::string Shader::getError() const
{
        GLint length = 0;
        GLsizei nchars = 0;
        glGetShaderiv(m_shaderHandle, GL_INFO_LOG_LENGTH, &length);
        std::unique_ptr<char[]> log = std::make_unique<char[]>(length);
        glGetShaderInfoLog(m_shaderHandle, length, &nchars, &log[0]);
        return std::string(log.get());
}

} // namespace glwrapping
} // namespace graphics
} // namespace vngine
