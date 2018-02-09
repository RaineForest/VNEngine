
#include "Exceptions.h"
#include "graphics/Shader.h"

namespace vngine {
namespace graphics {

template<GLenum ShaderType>
Shader::Shader(std::string src) :
        m_source(src),
        m_type(ShaderType)
{
        // create the handle
        m_shaderHandle = glCreateShader(ShaderType);

        // attach the source to the handle
        GLchar* psource = static_cast<GLchar*>(m_source.c_str());
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
        glGetShaderInfoLog(m_shaderHandle, length, &nchars, log);
        return std::string(log.get());
}

} // namespace graphics
} // namespace vngine
