#pragma once 

#include "graphics/IDrawable.h"

#include <glm/gtc/matrix_transform.hpp>

namespace vngine {
namespace graphics {

class IModel : public IDrawable {
public:
        IModel() = default;
        virtual ~IModel() = default;

        void rotate(float angle, glm::vec3 axis);
        void translate(glm::vec3 move);
        void scale(glm::vec3 scale);

protected:
        glm::mat4 modelTransform{1.0f};
};

} // namespace graphics
} // namespace vngine
