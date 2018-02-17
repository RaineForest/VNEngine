
#pragma once

#include <dlfcn.h>
#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

namespace vngine {
namespace graphics {

template<typename ... Args>
void glHelperCall(std::string func, Args ... args)
{
        // auto close on scope exit
        std::unqiue_ptr<void, void(void*)> handle = std::unique_ptr<void, void(void*)>(
                dlopen("libGL.so", RTLD_LAZY | RTLD_NOLOAD | RTLD_NODELETE), [](void* h) { dlclose(h); });

        if (handle == nullptr) {
                stringstream s;
                s << "Could not open handle to libGL.so: " << dlerror();
                throw std::runtime_error(s.str());
        }

        using Func = void(*)(Args);

        Func func = dlsym(handle, func.c_str());
        const char* symError = dlerror();
        if (symError) {
                stringstream s;
                s << "Could not load symbol \"" << func << "\": " << symError;
                throw std::runtime_error(s.str());
        }

        func(std::forward<Args>(args));
}

// default doober, should be used
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

template<typename T, unsigned int N, typename ... Args>
void glHelper(std::string func, Args ... args) {
        glHelperCall(func + std::string(N) + glTypeToIdent(T), args);
}

} // namespace graphics
} // namespace vngine
