
#include "Exceptions.h"
#include "graphics/glwrapping/GLHelper.h"
#include "graphics/glwrapping/ShaderProgram.h"

#include <algorithm>
#include <memory>
#include <vector>

using namespace gl;

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
        if (!flag) {
                std::string err("Shader program link error:\n");
                err += getError();
                throw GLException(err);
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
        std::vector<char> log(length);
        glGetShaderInfoLog(m_programHandle, length, &nchars, log.data());
        return std::string(log.begin(), log.end());
}

} // namespace glwrapping
} // namespace graphics
} // namespace vngine
