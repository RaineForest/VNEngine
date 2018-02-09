
#pragma once

#include "graphics/Shader.h"
#include <string>
#include <vector>

namespace vngine {
namespace graphics {

class ShaderProgram
{
public:
        template<GLenum ShaderType>
        ShaderProgram();
        virtual ~ShaderProgram();

        template<typename ShaderType>
        void set(const std::vector<Shader<ShaderType>>& s);

        void use() const;

        // TODO: binding and setting attributes

private:
        std::string getError() const;

        std::vector<GLuint> m_shaders;
        GLuint m_programHandle;
};

} // namespace graphics
} // namespace vngine
