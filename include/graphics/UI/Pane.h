
#pragma once

#include "graphics/UI/IContainer.h"

namespace vngine {
namespace graphics {
namespace ui {

/**
 * Basic container for holding other drawables
 */
class Pane : public IContainer
{
public:
        Pane()
        {
        }

        virtual ~Pane()
        {
        }

        virtual void add(IDrawable& obj)
        {
        }

        virtual void remove(IDrawable& obj)
        {
        }
        
        virtual void draw(const ICamera& camera) const
        {
        }
};

} // namespace ui
} // namespace graphics
} // namespace vngine
