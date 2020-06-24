
#pragma once

namespace vngine {
namespace graphics {

/**
 * Interface for describing drawable objects
 */
template<typename T, unsigned int Dim>
class IDrawable
{
public:
        virtual ~IDrawable() = default;

        /**
         * Draws the object 
         */
        virtual void draw() const = 0;
};

} // namespace graphics
} // namespace vngine
