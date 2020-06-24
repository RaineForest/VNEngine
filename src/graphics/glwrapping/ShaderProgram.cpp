
#include "Exceptions.h"
#include "graphics/glwrapping/GLHelper.h"
#include "graphics/glwrapping/ShaderProgram.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace vngine {
namespace graphics {
namespace glwrapping {

ShaderProgram::ShaderProgram()
{
        m_programHandle = GL_CHECK(glCreateProgram());
}

ShaderProgram::~ShaderProgram()
{
        glDeleteProgram(m_programHandle);
}

void ShaderProgram::setShaders(const std::vector<std::shared_ptr<Shader>>& s)
{
        std::for_each(m_shaders.begin(), m_shaders.end(), [this](std::shared_ptr<Shader>& shader) {
                GL_CHECK(glDetachShader(this->m_programHandle, shader->getHandle()));
        });
        m_shaders.clear();
        std::for_each(s.begin(), s.end(), [this](const std::shared_ptr<Shader>& x) {
                this->m_shaders.push_back(x);
                GL_CHECK(glAttachShader(this->m_programHandle, x->getHandle()));
        });
        GL_CHECK(glLinkProgram(m_programHandle));
        GLint flag;
        GL_CHECK(glGetProgramiv(m_programHandle,  GL_LINK_STATUS, &flag));
        if (flag == GL_FALSE) {
                std::string err("Shader program link error:\n");
                err += getError();
                throw GLException(err);
        }
}

void ShaderProgram::use() const
{
        GL_CHECK(glUseProgram(m_programHandle));
}

std::string ShaderProgram::getError() const
{
        GLint length = 0;
        GLsizei nchars = 0;
        GL_CHECK(glGetProgramiv(m_programHandle, GL_INFO_LOG_LENGTH, &length));
        std::vector<char> log(length);
        GL_CHECK(glGetShaderInfoLog(m_programHandle, length, &nchars, log.data()));
        return std::string(log.begin(), log.end());
}

} // namespace glwrapping
} // namespace graphics
} // namespace vngine
