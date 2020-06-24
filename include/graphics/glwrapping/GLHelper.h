
#pragma once

#include <cassert>
#include <dlfcn.h>
#include <functional>
#include <GL/glew.h>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

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
        boundFunc(std::forward<Args>(args)...);
}

// default doober, should not be used
template<typename T> inline
std::string glTypeToIdent(T)
{
        assert(false /* unsupported type */);
        return std::string(typeid(T).name());
}

template<> inline
std::string glTypeToIdent<int>(int)
{
        return std::string("i");
}

template<> inline
std::string glTypeToIdent<float>(float)
{
        return std::string("f");
}

template<> inline
std::string glTypeToIdent<unsigned int>(unsigned int)
{
        return std::string("ui");
}

template<> inline
std::string glTypeToIdent<short>(short)
{
        return std::string("s");
}

template<> inline
std::string glTypeToIdent<double>(double)
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
template<typename T, typename ... Args>
void glHelper(std::string func, unsigned int meatyArity, Args ... args) {
        glHelperCall(func + std::to_string(meatyArity) + glTypeToIdent<T>(0), std::forward<Args>(args)...);
}

template<typename T, typename ... Args>
void glHelper(std::string func, unsigned int meatyArity, T* array, Args ... args) {
        glHelperCall(func + std::to_string(meatyArity) + glTypeToIdent<T>(0) + std::string("v"),
                     std::forward<Args>(args)...,
                     array);
}

template<typename T> inline
GLenum glTypeToEnum(T)
{
        assert(false /* unsupported type */);
        return 0;
}

template<> inline
GLenum glTypeToEnum<char>(char)
{
        return GL_BYTE;
}

template<> inline
GLenum glTypeToEnum<unsigned char>(unsigned char)
{
        return GL_UNSIGNED_BYTE;
}

template<> inline
GLenum glTypeToEnum<short>(short)
{
        return GL_SHORT;
}

template<> inline
GLenum glTypeToEnum<unsigned short>(unsigned short)
{
        return GL_UNSIGNED_SHORT;
}

template<> inline
GLenum glTypeToEnum<int>(int)
{
        return GL_INT;
}

template<> inline
GLenum glTypeToEnum<unsigned int>(unsigned int)
{
        return GL_UNSIGNED_INT;
}

template<> inline
GLenum glTypeToEnum<float>(float)
{
        return GL_FLOAT;
}

template<> inline
GLenum glTypeToEnum<double>(double)
{
        return GL_DOUBLE;
}

} // namespace glwrapping
} // namespace graphics
} // namespace vngine
