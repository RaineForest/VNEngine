#include "graphics/IModel.h"

namespace vngine {
namespace graphics {

void IModel::rotate(float angle, glm::vec3 axis)
{
        modelTransform = glm::rotate(modelTransform, angle, axis);
}

void IModel::translate(glm::vec3 move)
{
        modelTransform = glm::translate(modelTransform, move);
}

void IModel::scale(glm::vec3 scale)
{
        modelTransform = glm::scale(modelTransform, scale);
}

} // namespace graphics
} // namespace vngine
