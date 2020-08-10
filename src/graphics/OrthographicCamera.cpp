#include "graphics/OrthographicCamera.h"

namespace vngine {
namespace graphics {

OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
        : projection(glm::ortho(left, right, top, bottom))
{
}

glm::mat4 OrthographicCamera::getProjection() const
{
        return projection;
}

} // namespace graphics
} // namespace vngine

