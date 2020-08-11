
#pragma once

#include <GL/glew.h>

#include <execinfo.h>
#include <functional>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <string>

namespace vngine
{

class VNgineException : public std::exception
{
public:
        VNgineException(std::string msg) 
        {
                constexpr int bufferSize = 4096;
                void* buffer[bufferSize];
                int actualSize = backtrace(buffer, bufferSize);
                auto symbols = std::unique_ptr<char*, std::function<void(char**)>>(backtrace_symbols(buffer, actualSize), [](char** c) {
                        free(c);
                });

                std::string stackTrace = "";
                for (int i = 0; i < actualSize; i++) {
                        stackTrace += std::string(symbols.get()[i]) + "\n";
                }

                std::stringstream ss;
                ss << msg << "\nStack Trace:\n" << stackTrace;
                m_msg = ss.str();
        }

        virtual ~VNgineException() = default;

        virtual const char* what() const noexcept override
        {
                return m_msg.c_str();
        }

private:
        std::string m_msg{""};
};

class GLException : public VNgineException
{
public:
        GLException(std::string msg) : VNgineException(std::string("GLException: ") + msg) {}
        GLException(GLenum code) : VNgineException(std::string("GLException: ") + glErrorString(code)) {}
        virtual ~GLException() {}

private:
        static std::string glErrorString(GLenum error) {
                switch (error) {
                case GL_NO_ERROR:
                        return "No error";
                case GL_INVALID_ENUM:
                        return "Invalid enum";
                case GL_INVALID_VALUE:
                        return "Invalid value";
                case GL_INVALID_OPERATION:
                        return "Invalid operation";
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                        return "Invalid framebuffer operation";
                case GL_OUT_OF_MEMORY:
                        return "Out of memory";
                case GL_STACK_UNDERFLOW:
                        return "Stack underflow";
                case GL_STACK_OVERFLOW:
                        return "Stack overflow";
                default:
                        return "Unknown error " + std::to_string(error);
        }
}

}; 

} //namespace vngine
