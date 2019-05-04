
#pragma once

#include "graphics/geometry/Point.h"
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

using graphics::geometry::Vector;

class ShaderProgram
{
public:
        ShaderProgram();
        virtual ~ShaderProgram();

        void setShaders(const std::vector<Shader>& s);

        void use() const;

        template<typename T, unsigned int N>
        void setUniform(const std::string& binding, Vector<T, N> v) const;

        template<typename T, unsigned int N>
        void setInput(const std::string& binding, const VertexArray& array, const MultiAttribBuffer<T, N>& buf, unsigned int subBuffer) const;

private:
        std::string getError() const;

        std::vector<gl::GLuint> m_shaders;
        gl::GLuint m_programHandle;
};

template<typename T, unsigned int N>
void ShaderProgram::setUniform(const std::string& binding, Vector<T, N> v) const
{
        gl::GLuint var = gl::glGetAttribLocation(m_programHandle, binding.c_str());
        glHelper<T>("glUniform", N, static_cast<T*>(v), var, N);
}

template<typename T, unsigned int N>
void ShaderProgram::setInput(const std::string& binding, const VertexArray& array, const MultiAttribBuffer<T, N>& buf, unsigned int subBuffer) const
{
        gl::GLuint handle = gl::glGetAttribLocation(m_programHandle, binding.c_str());
        array.setBuffer(handle, buf, subBuffer);
}

} // namespace glwrapping
} // namespace graphics
} // namespace vngine
