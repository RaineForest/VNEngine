#include "graphics/RawModel.h"

#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <cstring>

namespace vngine {
namespace graphics {

RawModel::RawModel(const std::vector<glm::vec3>& verts, std::shared_ptr<glwrapping::ShaderProgram> shader) :
        numVerts(verts.size()),
        shader(shader)
{
        std::unique_ptr<float[]> v = std::make_unique<float[]>(numVerts * 3);
        for(size_t i = 0; i < verts.size(); i++) {
                v[i * 3 + 0] = verts[i].x;
                v[i * 3 + 1] = verts[i].y;
                v[i * 3 + 2] = verts[i].z;
        }

        arr.bind();
        vertBuffer = std::make_unique<vngine::graphics::glwrapping::MultiAttribBuffer<float, 1>>(
                GL_ARRAY_BUFFER,
                std::move(v),
                9,
                std::array<unsigned int, 1>({3}),
                std::array<unsigned int, 1>({sizeof(float) * 3}),
                std::array<void*, 1>({0})
        );
}

void RawModel::draw(const ICamera& camera) const {
        shader->setInput("vPosition", arr, *vertBuffer, 0);

        shader->use();
        shader->setUniformMatrix("projection", glm::value_ptr(camera.getProjection()), 4);
        shader->setUniformMatrix("view", glm::value_ptr(camera.getView()), 4);
        shader->setUniformMatrix("model", glm::value_ptr(modelTransform), 4);
        arr.bind();
        glDrawArrays(GL_TRIANGLES, 0, numVerts);
}

} // namespace graphics
} // namespace vngine
