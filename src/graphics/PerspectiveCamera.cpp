#include "graphics/PerspectiveCamera.h"

namespace vngine {
namespace graphics {

PerspectiveCamera::PerspectiveCamera(float viewAngle, float aspectRatio, float near, float far)
        : projection(glm::perspective(viewAngle, aspectRatio, near, far))
{
}

glm::mat4 PerspectiveCamera::getProjection() const
{
        return projection;
}

} // namespace graphics
} // namespace vngine

