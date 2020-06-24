
#include "graphics/glwrapping/MultiAttribBuffer.h"
#include "graphics/glwrapping/GLHelper.h"
#include "graphics/glwrapping/Shader.h"
#include "graphics/glwrapping/ShaderProgram.h"
#include "graphics/glwrapping/VertexArray.h"
#include "graphics/IDrawable.h"
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

static constexpr float vertices[9] = {
        cosf((3.0f / 6.0f) * M_PI),  sinf((3.0f / 6.0f) * M_PI), 0.0f,
        cosf((7.0f / 6.0f) * M_PI),  sinf((7.0f / 6.0f) * M_PI), 0.0f,
        cosf((11.0f / 6.0f) * M_PI),  sinf((11.0f / 6.0f) * M_PI), 0.0f,
};

class Triangle : public vngine::graphics::IDrawable<float, 3>
{
public:
        Triangle() :
                program()
        {
                auto vertShader = std::make_shared<vngine::graphics::glwrapping::Shader>(GL_VERTEX_SHADER, basicVertShader);
                auto fragShader = std::make_shared<vngine::graphics::glwrapping::Shader>(GL_FRAGMENT_SHADER, basicFragShader);
                program.setShaders(std::vector<std::shared_ptr<vngine::graphics::glwrapping::Shader>>({vertShader, fragShader}));

                std::unique_ptr<float[]> verts = std::make_unique<float[]>(9);
                memcpy(verts.get(), vertices, sizeof(float)*9);

                arr.bind();
                vertBuffer = std::make_unique<vngine::graphics::glwrapping::MultiAttribBuffer<float, 1>>(
                        GL_ARRAY_BUFFER,
                        std::move(verts),
                        9,
                        std::array<unsigned int, 1>({3}),
                        std::array<unsigned int, 1>({sizeof(float) * 3}),
                        std::array<void*, 1>({0})
                );

                program.setInput("vPosition", arr, *vertBuffer, 0);

                projection = glm::perspective(glm::radians(45.0f), 16.0f/9.0f, 0.1f, 100.0f);
                view = glm::mat4(1.0f);
                view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
                model = glm::mat4(1.0f);
        }

        virtual void draw() const override
        {
                program.use();
                program.setUniformMatrix("projection", glm::value_ptr(projection), 4);
                program.setUniformMatrix("view", glm::value_ptr(view), 4);
                program.setUniformMatrix("model", glm::value_ptr(model), 4);
                arr.bind();
                glDrawArrays(GL_TRIANGLES, 0, 3);
        }

private:
        std::unique_ptr<vngine::graphics::glwrapping::MultiAttribBuffer<float, 1>> vertBuffer;
        vngine::graphics::glwrapping::VertexArray arr;
        vngine::graphics::glwrapping::ShaderProgram program;

        glm::mat4 projection;
        glm::mat4 view;
        glm::mat4 model;
};

int main()
{
        try {
                vngine::init::GameInit3D my_init;

                std::unique_ptr<Triangle> tri = std::make_unique<Triangle>();
                my_init.add(std::move(tri));

                my_init.start();

                return 0;
        } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                return 1;
        }
}
