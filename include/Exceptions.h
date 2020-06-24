
#pragma once

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

                std::string stackTrace;
                for (int i = 0; i < actualSize; i++) {
                        stackTrace += std::string(symbols.get()[i]) + "\n";
                }

                std::stringstream ss;
                ss << msg << "\nStack Trace:\n" << stackTrace;
                m_msg = ss.str();
        }

        virtual ~VNgineException() {}

        virtual const char* what() const noexcept override
        {
                return m_msg.c_str();
        }

private:
        std::string m_msg;
};

class GLException : public VNgineException
{
public:
        GLException(std::string msg) : VNgineException(std::string("GLException: ") + msg) {}
        virtual ~GLException() {}
}; 

} //namespace vngine
