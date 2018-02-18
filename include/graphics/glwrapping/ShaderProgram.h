
#pragma once

#include "graphics/geometry/Point.h"
#include "graphics/glwrapping/Buffer.h"
#include "graphics/glwrapping/GLHelper.h"
#include "graphics/glwrapping/MultiAttribBuffer.h"
#include "graphics/glwrapping/Shader.h"

#include <string>
#include <vector>

namespace vngine {
namespace graphics {
namespace glwrapping {

using graphics::geometry::Vector;

class ShaderProgram
{
public:
        ShaderProgram();
        virtual ~ShaderProgram();

        void setShaders(const std::vector<Shader>& s);

        void use() const;

        template<typename T, unsigned int N>
        void setUniform(std::string binding, Vector<T, N> v) const;

        template<typename T, unsigned int N>
        void setInput(std::string binding, const MultiAttribBuffer<T, N>& buf, unsigned int subBuffer) const;

private:
        std::string getError() const;

        std::vector<GLuint> m_shaders;
        GLuint m_programHandle;
};

template<typename T, unsigned int N>
void ShaderProgram::setUniform(std::string binding, Vector<T, N> v) const
{
        GLuint var = glGetUniformLocation(m_programHandle, binding.c_str());
        glHelper<T>("glUniform", N, static_cast<T*>(v), var, N);
}

template<typename T, unsigned int N>
void ShaderProgram::setInput(std::string binding, const MultiAttribBuffer<T, N>& buf, unsigned int subBuffer) const
{
        GLuint handle = glGetAttribLocation(m_programHandle, binding.c_str());
        glEnableVertexAttribArray(handle);
        glVertexAttribPointer(handle,
                              buf.getNumComponents(subBuffer),
                              glTypeToEnum<T>(),
                              GL_FALSE,
                              buf.getStride(subBuffer),
                              buf.getOffset(subBuffer)); 
}

} // namespace glwrapping
} // namespace graphics
} // namespace vngine
