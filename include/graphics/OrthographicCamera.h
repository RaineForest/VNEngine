#pragma once

#include "graphics/ICamera.h"

namespace vngine {
namespace graphics {

class OrthographicCamera : public ICamera {
public:
        OrthographicCamera(float left, float right, float top, float bottom);
        virtual ~OrthographicCamera() = default;

        virtual glm::mat4 getProjection() const override;

private:
        glm::mat4 projection;
};

} // namespace graphics
} // namespace vngine
