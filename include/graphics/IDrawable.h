
#pragma once

#include "graphics/ICamera.h"

namespace vngine {
namespace graphics {

/**
 * Interface for describing drawable objects
 */
class IDrawable
{
public:
        virtual ~IDrawable() = default;

        /**
         * Draws the object 
         */
        virtual void draw(const ICamera& camera) const = 0;
};

} // namespace graphics
} // namespace vngine
