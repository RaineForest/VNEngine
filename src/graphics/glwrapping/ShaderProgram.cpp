
#include "Exceptions.h"
#include "graphics/glwrapping/GLHelper.h"
#include "graphics/glwrapping/ShaderProgram.h"

#include <algorithm>
#include <memory>

namespace vngine {
namespace graphics {
namespace glwrapping {

ShaderProgram::ShaderProgram()
{
        m_programHandle = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
        glDeleteProgram(m_programHandle);
}

void ShaderProgram::setShaders(const std::vector<Shader>& s)
{
        std::for_each(m_shaders.begin(), m_shaders.end(), [this](GLuint& shader) {
                glDetachShader(this->m_programHandle, shader);
        });
        m_shaders.clear();
        std::for_each(s.begin(), s.end(), [this](const Shader& x) {
                this->m_shaders.push_back(x.getHandle());
                glAttachShader(this->m_programHandle, x.getHandle());
        });
        glLinkProgram(m_programHandle);
        GLint flag;
        glGetProgramiv(m_programHandle,  GL_LINK_STATUS, &flag);
        if (flag == GL_FALSE) {
                throw GLException("Shader program link error: " + getError());
        }
}

void ShaderProgram::use() const
{
        glUseProgram(m_programHandle);
}

std::string ShaderProgram::getError() const
{
        GLint length = 0;
        GLsizei nchars = 0;
        glGetProgramiv(m_programHandle, GL_INFO_LOG_LENGTH, &length);
        std::unique_ptr<char[]> log = std::make_unique<char[]>(length);
        glGetProgramInfoLog(m_programHandle, length, &nchars, &log[0]);
        return std::string(log.get());
}

} // namespace glwrapping
} // namespace graphics
} // namespace vngine
