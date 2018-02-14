
#pragma once

#include "graphics/UI/IContainer.h"

namespace vngine {
namespace graphics {
namespace ui {

/**
 * Basic container for holding other drawables
 */
template<typename T>
class Pane : public IContainer<T>
{
public:
        Pane()
        {
        }

        virtual ~Pane()
        {
        }

        virtual void add(IDrawable* obj)
        {
        }

        virtual void remove(IDrawable* obj)
        {
        }
        
        virtual void draw() const
        {
        }
};

} // namespace ui
} // namespace graphics
} // namespace vngine
