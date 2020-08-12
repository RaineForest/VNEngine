#pragma once

#include <glm/gtc/matrix_transform.hpp>

namespace vngine {
namespace graphics {

class ICamera {
public:
        ICamera() = default;
        virtual ~ICamera() = default;

        glm::mat4 getView() const;
        virtual glm::mat4 getProjection() const = 0;

        void rotate(float angle, glm::vec3 axis);
        void translate(glm::vec3 move);

private:
        glm::mat4 view{glm::lookAt(glm::vec3{0.f, 0.f, 0.f}, glm::vec3{0.f, 0.f, -1.f}, glm::vec3{0.f, 1.f, 0.f})};
};

} // namespace graphics
} // namespace vngine
