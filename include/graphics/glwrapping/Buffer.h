
#pragma once

#include <GL/glew.h>
#include <memory>

namespace vngine {
namespace graphics {
namespace glwrapping {

template<typename T>
class Buffer
{
public:
        Buffer(GLenum type, std::unique_ptr<T[]> buffer, unsigned int num);
        virtual ~Buffer();

        virtual void bind() const;

        virtual GLuint handle() const;
        virtual unsigned long size() const;
        virtual unsigned int elementCount() const;
        virtual GLenum type() const;

private:
        GLuint m_handle;
        unsigned int m_numElements;
        unsigned long m_totalSize;
        GLenum m_type;
        std::unique_ptr<T[]> m_buffer;
};

template<typename T>
Buffer<T>::Buffer(GLenum type, std::unique_ptr<T[]> buffer, unsigned int num) :
        m_type(type),
        m_numElements(num),
        m_totalSize(num * sizeof(T)),
        m_buffer(std::move(buffer))
{
        glGenBuffers(1, &m_handle);
        glBindBuffer(m_type, m_handle);
        glBufferData(m_type, m_totalSize, m_buffer.get(), GL_STATIC_DRAW);
}

template<typename T>
Buffer<T>::~Buffer()
{
        glDeleteBuffers(1, &m_handle);
}

template<typename T>
void Buffer<T>::bind() const
{
        glBindBuffer(m_type, m_handle);
}

template<typename T>
GLuint Buffer<T>::handle() const
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
GLenum Buffer<T>::type() const
{
        return m_type;
}

} //namespace glwrapping
} //namespace graphics
} //namespace vngine
