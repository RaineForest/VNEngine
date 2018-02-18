
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
        std::unique_ptr<void, decltype(deleter)> handle(
                // TODO: cross-platform and configurable lib name
                dlopen("libGL.so", RTLD_LAZY | RTLD_NOLOAD | RTLD_NODELETE),
                deleter
        );

        if (handle == nullptr) {
                std::stringstream s;
                s << "Could not open handle to libGL.so: " << dlerror();
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
template<typename T>
std::string glTypeToIdent()
{
        assert(false /* unsupported type */);
        return std::string(typeid(T).name());
}

template<>
std::string glTypeToIdent<int>()
{
        return std::string("i");
}

template<>
std::string glTypeToIdent<float>()
{
        return std::string("f");
}

template<>
std::string glTypeToIdent<unsigned int>()
{
        return std::string("ui");
}

template<>
std::string glTypeToIdent<short>()
{
        return std::string("s");
}

template<>
std::string glTypeToIdent<double>()
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
        glHelperCall(func + std::to_string(meatyArity) + glTypeToIdent<T>(), std::forward<Args>(args)...);
}

template<typename T, typename ... Args>
void glHelper(std::string func, unsigned int meatyArity, T* array, Args ... args) {
        glHelperCall(func + std::to_string(meatyArity) + glTypeToIdent<T>() + std::string("v"),
                     std::forward<Args>(args)...,
                     array);
}

template<typename T>
GLenum glTypeToEnum()
{
        assert(false /* unsupported type */);
        return 0;
}

template<>
GLenum glTypeToEnum<char>()
{
        return GL_BYTE;
}

template<>
GLenum glTypeToEnum<unsigned char>()
{
        return GL_UNSIGNED_BYTE;
}

template<>
GLenum glTypeToEnum<short>()
{
        return GL_SHORT;
}

template<>
GLenum glTypeToEnum<unsigned short>()
{
        return GL_UNSIGNED_SHORT;
}

template<>
GLenum glTypeToEnum<int>()
{
        return GL_INT;
}

template<>
GLenum glTypeToEnum<unsigned int>()
{
        return GL_UNSIGNED_INT;
}

template<>
GLenum glTypeToEnum<float>()
{
        return GL_FLOAT;
}

template<>
GLenum glTypeToEnum<double>()
{
        return GL_DOUBLE;
}

} // namespace glwrapping
} // namespace graphics
} // namespace vngine
