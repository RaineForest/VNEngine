
#pragma once

#include "graphics/IDrawable.h"

namespace vngine {
namespace graphics {
namespace ui {

/**
 * Drawable container that holds other drawable objects
 */
class IContainer : public IDrawable
{
public:
        virtual ~IContainer() = 0;
        
        /**
         * add - add an element to the container
         * \param obj the object to add
         */
        virtual void add(IDrawable& obj) = 0;

        /**
         * remove - remove an element from the container
         * \param obj the object to remove
         */
        virtual void remove(IDrawable& obj) = 0;
};

} // namespace ui
} // namespace graphics
} // namespace vngine
