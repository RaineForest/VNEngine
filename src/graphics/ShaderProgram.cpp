
#include "Exceptions.h"
#include "graphics/ShaderProgram.h"

namespace vngine {
namespace graphics {

ShaderProgram::ShaderProgram()
{
        m_programHandle = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
        glDeleteProgram(m_programHandle);
}

template<typename ShaderType>
void ShaderProgram::set(const std::vector<Shader<ShaderType>>& s)
{
        std::for_each(m_shaders.begin(), m_shaders.end(), [this](GLuint shader) {
                glDetachShader(this->m_programHandle, shader);
        });
        m_shaders.clear();
        std::for_each(s.begin(), s.end(), [this](Shader<ShaderType> x) {
                this->m_shaders.push_back(x.getHandle());
                glAttachShader(this->m_programHandle, x.getHandle());
        });
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
        glGetProgramInfoLog(m_programHandle, length, &nchars, log);
        return std::string(log.get());
}

} // namespace graphics
} // namespace vngine
