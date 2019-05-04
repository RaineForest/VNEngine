
#pragma once

#include "glbinding/gl/gl.h"

#include <memory>

namespace vngine {
namespace graphics {
namespace glwrapping {

template<typename T>
class Buffer
{
public:
        Buffer();
        Buffer(gl::GLenum type, std::unique_ptr<T[]> buffer, unsigned int num);
        virtual ~Buffer();
        Buffer(Buffer&& other) = default;

        virtual void bind() const;

        virtual gl::GLuint handle() const;
        virtual unsigned long size() const;
        virtual unsigned int elementCount() const;
        virtual gl::GLenum type() const;

private:
        gl::GLuint m_handle;
        unsigned int m_numElements;
        unsigned long m_totalSize;
        gl::GLenum m_type;
        std::unique_ptr<T[]> m_buffer;
};

template<typename T>
Buffer<T>::Buffer(gl::GLenum type, std::unique_ptr<T[]> buffer, unsigned int num) :
        m_numElements(num),
        m_totalSize(num * sizeof(T)),
        m_type(type),
        m_buffer(std::move(buffer))
{
        gl::glGenBuffers(1, &m_handle);
        gl::glBindBuffer(m_type, m_handle);
        gl::glBufferData(m_type, m_totalSize, m_buffer.get(), gl::GL_STATIC_DRAW);
}

template<typename T>
Buffer<T>::~Buffer()
{
        gl::glDeleteBuffers(1, &m_handle);
}

template<typename T>
void Buffer<T>::bind() const
{
        gl::glBindBuffer(m_type, m_handle);
}

template<typename T>
gl::GLuint Buffer<T>::handle() const
{
        return m_handle;
}

template<typename T>
unsigned long Buffer<T>::size() const
{
        return m_totalSize;
}

template<typename T>
unsigned int Buffer<T>::elementCount() const
{
        return m_numElements;
}

template<typename T>
gl::GLenum Buffer<T>::type() const
{
        return m_type;
}

} //namespace glwrapping
} //namespace graphics
} //namespace vngine
