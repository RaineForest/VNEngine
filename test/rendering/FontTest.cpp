
#include "graphics/glwrapping/Shader.h"
#include "graphics/glwrapping/ShaderProgram.h"
#include "graphics/FreetypeFont.h"
#include "graphics/OrthographicCamera.h"
#include "init/GameInit3D.h"

#include <iostream>
#include <memory>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::string basicVertShader = R"(
#version 330 core

in vec3 vPosition;
in vec2 vertexUV;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out gl_PerVertex { vec4 gl_Position; };
out vec2 UVs;

void main() {
        gl_Position = projection * view * model * vec4(vPosition, 1.0);
        UVs = vertexUV;
}
)";

std::string basicFragShader = R"(
#version 330 core

in vec2 UVs;
uniform sampler2D tex;
out vec4 FragColor;

void main() {
        FragColor = vec4(1.0, 1.0, 1.0, texture(tex, UVs).r);
}
)";


int main()
{
        vngine::init::GameInit3D my_init(std::make_unique<vngine::graphics::OrthographicCamera>(0.f, 1280.f, 0.f, 720.f), false, 1280, 720);
        auto program = std::make_shared<vngine::graphics::glwrapping::ShaderProgram>();

        auto vertShader = std::make_shared<vngine::graphics::glwrapping::Shader>(GL_VERTEX_SHADER, basicVertShader);
        auto fragShader = std::make_shared<vngine::graphics::glwrapping::Shader>(GL_FRAGMENT_SHADER, basicFragShader);
        program->setShaders(std::vector<std::shared_ptr<vngine::graphics::glwrapping::Shader>>({vertShader, fragShader}));

        vngine::graphics::FreetypeFont font("/usr/share/fonts/gnu-free/FreeSans.ttf", 0);
        font.setSize(48);
        auto model = font.generate('b', program);
        model->translate(glm::vec3{-640.0f, 360.0f, 0.0f});
        my_init.add(std::move(model));

        my_init.start();

        return 0;
}
