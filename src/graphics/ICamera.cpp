#include "graphics/ICamera.h"

namespace vngine {
namespace graphics {

glm::mat4 ICamera::getView() const
{
        return view;
}

void ICamera::rotate(float angle, glm::vec3 axis)
{
        view = glm::rotate(view, angle, axis);
}

void ICamera::translate(glm::vec3 move)
{
        view = glm::translate(view, move);
}

} // namespace graphics
} // namespace vngine
