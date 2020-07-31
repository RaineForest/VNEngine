
#include "graphics/glwrapping/GLHelper.h"
#include "graphics/glwrapping/Shader.h"
#include "graphics/glwrapping/ShaderProgram.h"
#include "graphics/RawModel.h"
#include "init/GameInit3D.h"

#include <cstring>
#include <iostream>
#include <memory>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::string basicVertShader = R"(
#version 330 core

in vec3 vPosition;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out gl_PerVertex { vec4 gl_Position; };

void main() {
        gl_Position = projection * view * model * vec4(vPosition, 1.0);
}
)";

std::string basicFragShader = R"(
#version 330 core

out vec4 FragColor;

void main() {
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
)";

static const std::vector<glm::vec3> vertices{
        {cosf((3.0f / 6.0f) * M_PI),  sinf((3.0f / 6.0f) * M_PI), 0.0f},
        {cosf((7.0f / 6.0f) * M_PI),  sinf((7.0f / 6.0f) * M_PI), 0.0f},
        {cosf((11.0f / 6.0f) * M_PI),  sinf((11.0f / 6.0f) * M_PI), 0.0f}
};

int main()
{
        try {
                vngine::init::GameInit3D my_init;
                auto program = std::make_shared<vngine::graphics::glwrapping::ShaderProgram>();

                auto vertShader = std::make_shared<vngine::graphics::glwrapping::Shader>(GL_VERTEX_SHADER, basicVertShader);
                auto fragShader = std::make_shared<vngine::graphics::glwrapping::Shader>(GL_FRAGMENT_SHADER, basicFragShader);
                program->setShaders(std::vector<std::shared_ptr<vngine::graphics::glwrapping::Shader>>({vertShader, fragShader}));

                auto tri = std::make_unique<vngine::graphics::RawModel>(vertices, program);
                tri->translate(glm::vec3{0.0f, 0.0f, 3.0f});
                my_init.add(std::move(tri));

                my_init.start();

                return 0;
        } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                return 1;
        }
}
