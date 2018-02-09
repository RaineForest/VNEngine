
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

        virtual const char* what() const noexcept
        {
                return (prefix + m_msg).c_str();
        }

protected:
        virtual std::string prefix() const noexcept
        {
                return "VNgineException: ";
        }

        std::string m_msg;
}

class GLException : public VNgineException
{
public:
        GLException(std::string msg) : VNgineException(msg) {}
        virtual ~GLException() {}

protected:
        virtual std::string prefix() const noexcept
        {
                return "GLException: ";
        }
}; 

} //namespace vngine
