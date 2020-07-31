#pragma once

#include "graphics/ICamera.h"

namespace vngine {
namespace graphics {

class PerspectiveCamera : public ICamera {
public:
        PerspectiveCamera(float viewAngle, float aspectRatio, float near, float far);
        virtual ~PerspectiveCamera() = default;

        virtual glm::mat4 getProjection() const override;

private:
        glm::mat4 projection;
};

} // namespace graphics
} // namespace vngine
