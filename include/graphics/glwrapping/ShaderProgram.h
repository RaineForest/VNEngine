
#pragma once

#include "graphics/glwrapping/Buffer.h"
#include "graphics/glwrapping/GLHelper.h"
#include "graphics/glwrapping/MultiAttribBuffer.h"
#include "graphics/glwrapping/Shader.h"
#include "graphics/glwrapping/VertexArray.h"

#include <string>
#include <vector>

namespace vngine {
namespace graphics {
namespace glwrapping {

class ShaderProgram
{
public:
        ShaderProgram();
        virtual ~ShaderProgram();

        void setShaders(const std::vector<std::shared_ptr<Shader>>& s);

        void use() const;

        template<typename T>
        void setUniform(const std::string& binding, T* v, unsigned int dim, unsigned int N) const;
        template<typename T>
        void setUniformMatrix(std::string binding, T* v, unsigned int dim) const;

        template<typename T, unsigned int N>
        void setInput(const std::string& binding, const VertexArray& array, const MultiAttribBuffer<T, N>& buf, unsigned int subBuffer) const;

private:
        std::string getError() const;

        std::vector<std::shared_ptr<Shader>> m_shaders;
        GLuint m_programHandle;
};

template<typename T>
void ShaderProgram::setUniform(const std::string& binding, T* v, unsigned int dim, unsigned int N) const
{
        GLuint var = GL_CHECK(glGetUniformLocation(m_programHandle, binding.c_str()));
        GL_CHECK(glHelperArray<T>("glUniform", dim, v, var, N));
}

template<typename T>
void ShaderProgram::setUniformMatrix(std::string binding, T* v, unsigned int dim) const
{
        GLuint var = GL_CHECK(glGetUniformLocation(m_programHandle, binding.c_str()));
        GL_CHECK(glHelperArray<T>("glUniformMatrix", dim, v, var, static_cast<GLsizei>(1), static_cast<GLboolean>(GL_FALSE)));
        //GL_CHECK(glUniformMatrix4fv(var, 1, GL_FALSE, v));
}

template<typename T, unsigned int N>
void ShaderProgram::setInput(const std::string& binding, const VertexArray& array, const MultiAttribBuffer<T, N>& buf, unsigned int subBuffer) const
{
        GLuint handle = GL_CHECK(glGetAttribLocation(m_programHandle, binding.c_str()));
        array.setBuffer(handle, buf, subBuffer);
}

} // namespace glwrapping
} // namespace graphics
} // namespace vngine
