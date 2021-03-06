
#pragma once

#include "graphics/glwrapping/GLHelper.h"
#include "graphics/glwrapping/MultiAttribBuffer.h"

#include <GL/glew.h>
#include <memory>
#include <string>

namespace vngine {
namespace graphics {
namespace glwrapping {

class VertexArray
{
public:
        VertexArray();
        virtual ~VertexArray();
        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;
        VertexArray(VertexArray&&) = default;

        void bind() const;

        template<typename T, unsigned int N>
        void setBuffer(GLuint handle, const MultiAttribBuffer<T, N>& buf, unsigned int subBuffer) const;

private:
        GLuint m_vao;
};

template<typename T, unsigned int N>
void VertexArray::setBuffer(GLuint handle, const MultiAttribBuffer<T, N>& buf, unsigned int subBuffer) const
{
        GL_CHECK(glVertexAttribPointer(handle,
                              buf.getNumComponents(subBuffer),
                              glTypeToEnum<T>(0),
                              GL_FALSE,
                              buf.getStride(subBuffer),
                              buf.getOffset(subBuffer))); 
        GL_CHECK(glEnableVertexAttribArray(handle));
}

} // namespace glwrapping
} // namespace graphics
} // namespace vngine
