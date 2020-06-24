
#pragma once

#include <stdexcept>
#include <string>

namespace vngine
{

class VNgineException : public std::exception
{
public:
        VNgineException(std::string msg) :
                m_msg(msg)
        {}

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
