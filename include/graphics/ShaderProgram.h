
#pragma once

#include "graphics/Shader.h"
#include <string>
#include <vector>

namespace vngine {
namespace graphics {

class ShaderProgram
{
public:
        ShaderProgram();
        virtual ~ShaderProgram();

        void setShaders(const std::vector<Shader>& s);

        void use() const;

        // TODO: binding and setting attributes
        // void setUniform(std::string binding, )

private:
        std::string getError() const;

        std::vector<GLuint> m_shaders;
        GLuint m_programHandle;
};

} // namespace graphics
} // namespace vngine
