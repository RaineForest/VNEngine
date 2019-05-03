
#include "graphics/glwrapping/VertexArray.h"

namespace vngine {
namespace graphics {
namespace glwrapping {

VertexArray::VertexArray()
{
        glGenVertexArrays(1, &m_vao); 
}

VertexArray::~VertexArray()
{
        glDeleteVertexArrays(1, &m_vao);
}

void VertexArray::bind() const
{
        glBindVertexArray(m_vao);
}

} // namespace glwrapping
} // namespace graphics
} // namespace vngine
