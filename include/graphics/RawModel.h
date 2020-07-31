#pragma once

#include "graphics/IModel.h"

#include "graphics/glwrapping/MultiAttribBuffer.h"
#include "graphics/glwrapping/ShaderProgram.h"
#include "graphics/glwrapping/VertexArray.h"

#include <glm/ext/vector_float3.hpp>

#include <memory>
#include <vector>

namespace vngine {
namespace graphics {

class RawModel : public IModel {
public:
        RawModel(const std::vector<glm::vec3>& verts, std::shared_ptr<glwrapping::ShaderProgram> shader);
        virtual ~RawModel() = default;

        virtual void draw(const ICamera& camera) const override;

private:
        std::unique_ptr<vngine::graphics::glwrapping::MultiAttribBuffer<float, 1>> vertBuffer;
        vngine::graphics::glwrapping::VertexArray arr;
        unsigned int numVerts;

        std::shared_ptr<glwrapping::ShaderProgram> shader;
};

} // namespace graphics
} // namespace vngine
