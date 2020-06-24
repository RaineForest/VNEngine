
#include "graphics/glwrapping/Shader.h"

#include "graphics/glwrapping/GLHelper.h"

#include "Exceptions.h"

#include <memory>
#include <vector>

namespace vngine {
namespace graphics {
namespace glwrapping {

Shader::Shader(GLenum shaderType, std::string src) :
        m_source(src),
        m_type(shaderType)
{
        // create the handle
        m_shaderHandle = GL_CHECK(glCreateShader(shaderType));

        // attach the source to the handle
        const GLchar* psource = static_cast<const GLchar*>(m_source.c_str());
        GL_CHECK(glShaderSource(m_shaderHandle, 1, &psource, NULL));

        // compile the shader
        GL_CHECK(glCompileShader(m_shaderHandle));
        GLint flag;
        GL_CHECK(glGetShaderiv(m_shaderHandle, GL_COMPILE_STATUS, &flag));
        if (flag == GL_FALSE) {
                std::string s("Shader Compile error:\n");
                std::string err = getError();
                s += err;
                throw GLException(s);
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
        GL_CHECK(glGetShaderiv(m_shaderHandle, GL_INFO_LOG_LENGTH, &length));
        std::vector<char> log(length);
        GL_CHECK(glGetShaderInfoLog(m_shaderHandle, length, &nchars, log.data()));
        return std::string(log.begin(), log.end());
}

} // namespace glwrapping
} // namespace graphics
} // namespace vngine
