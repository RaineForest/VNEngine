
#pragma once

#include "graphics/IDrawable.h"

namespace vngine {
namespace graphics {
namespace geometry {

/**
 * Utility wrapper class for projecting/lifting Drawables
 */
template<typename T, unsigned int DestDim, unsigned int SrcDim>
class Projector : public IDrawable<T, DestDim>
{
public:
        Projector(const IDrawable<T, SrcDim>& src);
        virtual ~Projector();

        /**
         * Draw the object in to the new space transforming as necessary
         * SrcDim > DestDim: project the object onto a basic object (line, plane) using its orientation
         * SrcDim < DestDim: lift the object into in higher dimensional space as its basic object
         *                   (e.g. SrcDim = 2, object will be drawn as a plane, good for menus and text boxes)
         * SrcDim = DestDim: draw it as normal, do nothing special
         */
        void draw() const;

private:
        const IDrawable<T, SrcDim>& m_src;
};

} // namespace geometry
} // namespace graphics
} // namespace vngine
