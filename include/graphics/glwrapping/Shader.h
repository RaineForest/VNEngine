
#pragma once

#include "glbinding/gl/gl.h"
#include <string>

namespace vngine {
namespace graphics {
namespace glwrapping {

class Shader
{
public:
        Shader(gl::GLenum shaderType, std::string src);

        virtual ~Shader();

        gl::GLuint getHandle() const;

private:
        std::string getError() const;

        std::string m_source;
        gl::GLuint m_shaderHandle;
        gl::GLenum m_type;
};

} // namespace glwrapping
} // namespace graphics
} // namespace vngine
