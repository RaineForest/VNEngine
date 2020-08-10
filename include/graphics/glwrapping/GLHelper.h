
#pragma once

#include "Exceptions.h"

#include <cassert>
#include <dlfcn.h>
#include <functional>
#include <GL/glew.h>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#define GL_CHECK(X) (X); {GLenum _error = glGetError(); if (_error != GL_NO_ERROR) {throw vngine::GLException(std::string(reinterpret_cast<const char*>(gluErrorString(_error)))); }}

namespace vngine {
namespace graphics {
namespace glwrapping {

template<typename ... Args>
void glHelperCall(std::string func, Args ... args)
{
        // auto close on scope exit
        auto deleter = [](void* h) { dlclose(h); };
        // open the shared library
#ifndef VNGINE_OPENGL_LIB
#error VNGINE_OPENGL_LIB must be defined
#endif
        std::unique_ptr<void, decltype(deleter)> handle(
                dlopen(VNGINE_OPENGL_LIB, RTLD_LAZY | RTLD_NOLOAD | RTLD_NODELETE),
                deleter
        );

        if (handle == nullptr) {
                std::stringstream s;
                s << "Could not open handle to " << VNGINE_OPENGL_LIB << ": " << dlerror();
                throw std::runtime_error(s.str());
        }

        // make our function pointer type
        using Func = void(*)(Args...);

        // get our function pointer
        Func boundFunc = reinterpret_cast<Func>(dlsym(handle.get(), func.c_str()));
        const char* symError = dlerror();
        if (symError) {
                std::stringstream s;
                s << "Could not load symbol \"" << func << "\": " << symError;
                throw std::runtime_error(s.str());
        }

        // call it
        boundFunc(args...);
}

// default doober, should not be used
template<typename T> inline
std::string glTypeToIdent(const T&)
{
        throw GLException(std::string("glTypeToIdent: unknown type ") + typeid(T).name());
}

template<> inline
std::string glTypeToIdent<int>(const int&)
{
        return std::string("i");
}

template<> inline
std::string glTypeToIdent<float>(const float&)
{
        return std::string("f");
}

template<> inline
std::string glTypeToIdent<unsigned int>(const unsigned int&)
{
        return std::string("ui");
}

template<> inline
std::string glTypeToIdent<short>(const short&)
{
        return std::string("s");
}

template<> inline
std::string glTypeToIdent<double>(const double&)
{
        return std::string("d");
}

/**
 * glHelper - calls opengl functions of type gl.*[1-4][f,d,i,s,ui]() e.g. glVertex4f, glUniform3i
 * "meaty" in the following context refers to the meaningful values being passed on
 * 
 * Example:
 * glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
 *                  non-meaty       meaty       meaty       meaty
 * note glUniform(x)f : x == meatyArity
 * 
 * \param func the name of the function
 * \param type the type of the meaty params
 * \param meatyArity the arity of the meaty params
 * \param args ALL of the params to the function
 */
template<typename T, typename ...Args>
void glHelper(std::string func, unsigned int meatyArity, Args... args) {
        glHelperCall(func + std::to_string(meatyArity) + glTypeToIdent<T>(0), args...);
}

template<typename T, typename ...Args>
void glHelperArray(std::string func, unsigned int meatyArity, const T* array, Args... args) {
        glHelperCall(func + std::to_string(meatyArity) + glTypeToIdent<T>(0) + std::string("v"),
                     args...,
                     array);
}

template<typename T> inline
GLenum glTypeToEnum(const T&)
{
        throw GLException(std::string("glTypeToEnum: unknown type ") + typeid(T).name());
}

template<> inline
GLenum glTypeToEnum<char>(const char&)
{
        return GL_BYTE;
}

template<> inline
GLenum glTypeToEnum<unsigned char>(const unsigned char&)
{
        return GL_UNSIGNED_BYTE;
}

template<> inline
GLenum glTypeToEnum<short>(const short&)
{
        return GL_SHORT;
}

template<> inline
GLenum glTypeToEnum<unsigned short>(const unsigned short&)
{
        return GL_UNSIGNED_SHORT;
}

template<> inline
GLenum glTypeToEnum<int>(const int&)
{
        return GL_INT;
}

template<> inline
GLenum glTypeToEnum<unsigned int>(const unsigned int&)
{
        return GL_UNSIGNED_INT;
}

template<> inline
GLenum glTypeToEnum<float>(const float&)
{
        return GL_FLOAT;
}

template<> inline
GLenum glTypeToEnum<double>(const double&)
{
        return GL_DOUBLE;
}

} // namespace glwrapping
} // namespace graphics
} // namespace vngine
