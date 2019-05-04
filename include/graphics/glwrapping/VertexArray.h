
#pragma once

#include "graphics/glwrapping/MultiAttribBuffer.h"
#include "graphics/glwrapping/ShaderProgram.h"

#include "glbinding/gl/gl.h"
#include <memory>
#include <string>

namespace vngine {
namespace graphics {
namespace glwrapping {

class VertexArray
{
public:
        VertexArray() = default;
        ~VertexArray() = default;
        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;
        VertexArray(VertexArray&&) = default;

        void bind() const;

        template<typename T, unsigned int N>
        void setBuffer(gl::GLuint handle, const MultiAttribBuffer<T, N>& buf, unsigned int subBuffer) const;

private:
        gl::GLuint m_vao{0};
};

template<typename T, unsigned int N>
void VertexArray::setBuffer(gl::GLuint handle, const MultiAttribBuffer<T, N>& buf, unsigned int subBuffer) const
{
        gl::glVertexAttribPointer(handle,
                buf.getNumComponents(subBuffer),
                glTypeToEnum<T>(0),
                gl::GL_FALSE,
                buf.getStride(subBuffer),
                buf.getOffset(subBuffer)); 
        gl::glEnableVertexAttribArray(handle);
}

} // namespace glwrapping
} // namespace graphics
} // namespace vngine
