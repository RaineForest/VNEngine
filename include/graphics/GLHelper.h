
#pragma once

#include <cassert>
#include <dlfcn.h>
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace vngine {
namespace graphics {

template<typename ... Args>
void glHelperCall(std::string func, Args ... args)
{
        // auto close on scope exit
        auto deleter = [](void* h) { dlclose(h); };
        std::unique_ptr<void, decltype(deleter)> handle(
                dlopen("libGL.so", RTLD_LAZY | RTLD_NOLOAD | RTLD_NODELETE),
                deleter
        );

        if (handle == nullptr) {
                std::stringstream s;
                s << "Could not open handle to libGL.so: " << dlerror();
                throw std::runtime_error(s.str());
        }

        using Func = void(*)(Args...);

        Func boundFunc = reinterpret_cast<Func>(dlsym(handle.get(), func.c_str()));
        const char* symError = dlerror();
        if (symError) {
                std::stringstream s;
                s << "Could not load symbol \"" << func << "\": " << symError;
                throw std::runtime_error(s.str());
        }

        boundFunc(std::forward<Args>(args)...);
}

// default doober, should not be used
template<typename T>
std::string glTypeToIdent(T)
{
        assert(false /* unsupported type */);
        return std::string(typeid(T).name());
}

template<>
std::string glTypeToIdent<int>(int)
{
        return std::string("i");
}

template<>
std::string glTypeToIdent<float>(float)
{
        return std::string("f");
}

template<>
std::string glTypeToIdent<unsigned int>(unsigned int)
{
        return std::string("ui");
}

template<>
std::string glTypeToIdent<short>(short)
{
        return std::string("s");
}

template<>
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
void glHelper(std::string func, T type, unsigned int meatyArity, Args ... args) {
        glHelperCall(func + std::to_string(meatyArity) + glTypeToIdent(type), std::forward<Args>(args)...);
}

} // namespace graphics
} // namespace vngine
