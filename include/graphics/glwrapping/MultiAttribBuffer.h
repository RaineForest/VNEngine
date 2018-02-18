
#pragma once

#include <array>
#include <GL/glew.h>
#include <memory>

#include "graphics/glwrapping/Buffer.h"

namespace vngine {
namespace graphics {
namespace glwrapping {

template<typename T, unsigned int N>
class MultiAttribBuffer : public Buffer<T>
{
public:
        MultiAttribBuffer(GLenum type, std::unique_ptr<T[]> buffer, unsigned int num,
                          std::array<unsigned int, N>& numComponents,
                          std::array<unsigned int, N>& stride,
                          std::array<void*, N>& offset);
        virtual ~MultiAttribBuffer();

        virtual unsigned int getNumComponents(unsigned int subBuffer) const;
        virtual unsigned int getStride(unsigned int subBuffer) const;
        virtual void* getOffset(unsigned int subBuffer) const;

private:
        std::array<unsigned int, N> m_components;
        std::array<unsigned int, N> m_stride;
        std::array<void*, N> m_offsets;
};

template<typename T, unsigned int N>
MultiAttribBuffer<T, N>::MultiAttribBuffer(
        GLenum type,
        std::unique_ptr<T[]> buffer,
        unsigned int num,
        std::array<unsigned int, N>& numComponents,
        std::array<unsigned int, N>& stride,
        std::array<void*, N>& offset) :
        Buffer<T>(type, std::move(buffer), num), // super constructor
        m_components(numComponents),
        m_stride(stride),
        m_offsets(offset)
{
}

template<typename T, unsigned int N>
MultiAttribBuffer<T, N>::~MultiAttribBuffer()
{
}

template<typename T, unsigned int N>
unsigned int MultiAttribBuffer<T, N>::getNumComponents(unsigned int subBuffer) const
{
        if (subBuffer >= N) {
                throw std::out_of_range("Sub-buffer access out of range!");
        }
        return m_components[subBuffer];
}

template<typename T, unsigned int N>
unsigned int MultiAttribBuffer<T, N>::getStride(unsigned int subBuffer) const
{
        if (subBuffer >= N) {
                throw std::out_of_range("Sub-buffer access out of range!");
        }
        return m_stride[subBuffer];
}

template<typename T, unsigned int N>
void* MultiAttribBuffer<T, N>::getOffset(unsigned int subBuffer) const
{
        if (subBuffer >= N) {
                throw std::out_of_range("Sub-buffer access out of range!");
        }
        return m_offsets[subBuffer];
}

} //namespace glwrapping
} //namespace graphics
} //namespace vngine
