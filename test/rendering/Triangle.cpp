
#include "graphics/glwrapping/MultiAttribBuffer.h"
#include "graphics/glwrapping/GLHelper.h"
#include "graphics/glwrapping/Shader.h"
#include "graphics/glwrapping/ShaderProgram.h"
#include "graphics/glwrapping/VertexArray.h"
#include "graphics/IDrawable.h"
#include "init/GameInit3D.h"

#include "glbinding/gl/gl.h"

#include <cstring>
#include <iostream>
#include <memory>
#include <string>

using namespace gl;

std::string basicVertShader = R"(
#version 330 core

in vec3 vPosition;
out gl_PerVertex { vec4 gl_Position; };

void main() {
        gl_Position.xyz = vPosition;
        gl_Position.w = 1.0;
}
)";

std::string basicFragShader = R"(
#version 330 core

out vec3 color;

void main() {
        color = vec3(1.0, 0.0, 0.0);
}
)";

static constexpr float vertices[9] = {
        -1.0f, -1.0f, 0.0f,
        1.0f,  -1.0f, 0.0f,
        0.0f,   1.0f, 0.0f
};

class Triangle : public vngine::graphics::IDrawable<float, 3>
{
public:
        Triangle() :
                program()
        {
                std::unique_ptr<float[]> verts = std::make_unique<float[]>(9);
                memcpy(verts.get(), vertices, sizeof(float)*9);

                vertBuffer = std::make_unique<vngine::graphics::glwrapping::MultiAttribBuffer<float, 1>>(
                        gl::GLenum::GL_ARRAY_BUFFER,
                        std::move(verts),
                        3,
                        std::array<unsigned int, 1>({3}),
                        std::array<unsigned int, 1>({0}),
                        std::array<void*, 1>({0})
                );

                vngine::graphics::glwrapping::Shader vertShader(gl::GLenum::GL_VERTEX_SHADER, basicVertShader);
                vngine::graphics::glwrapping::Shader fragShader(gl::GLenum::GL_FRAGMENT_SHADER, basicFragShader);
                program.setShaders(std::vector<vngine::graphics::glwrapping::Shader>({vertShader, fragShader}));
        }

        virtual void draw() const override
        {
                program.use();
                vngine::graphics::glwrapping::VertexArray array;
                vertBuffer->bind();
                program.setInput("vPosition", array, *vertBuffer, 0);
                glDrawArrays(GL_TRIANGLES, 0, 3);
        }

private:
        std::unique_ptr<vngine::graphics::glwrapping::MultiAttribBuffer<float, 1>> vertBuffer;
        vngine::graphics::glwrapping::ShaderProgram program;
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
