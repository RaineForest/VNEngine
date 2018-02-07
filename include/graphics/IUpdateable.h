
#pragma once

#include <chrono>

namespace vngine {
namespace graphics {

/**
 * Interface for describing updateable objects
 */
class IUpdateable
{
public:
        virtual ~IUpdateable() = 0;

        /**
         * Updates the object 
         * \param dt (time delta) the number of milliseconds since the last update
         */
        virtual void update(std::chrono::milliseconds dt) = 0;
};

} // namespace graphics
} // namespace vngine
