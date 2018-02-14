
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
        Projector(const IDrawable<T, SrcDim>& src) :
                m_src(src)
        {
        }

        virtual ~Projector()
        {
        }

        /**
         * Draw the object in to the new space transforming as necessary
         * SrcDim > DestDim: project the object onto a basic object (line, plane) using its orientation
         * SrcDim < DestDim: lift the object into in higher dimensional space as its basic object
         *                   (e.g. SrcDim = 2, object will be drawn as a plane, good for menus and text boxes)
         * SrcDim = DestDim: draw it as normal, do nothing special
         */
        template<typename std::enable_if_t<(DestDim == SrcDim)>::type* = nullptr>
        void draw() const override
        {
                m_src.draw();
        }

        template<typename std::enable_if_t<(DestDim > SrcDim)>::type* = nullptr>
        void draw() const override
        {
                /* steps:
                * 1. push a transformation matrix (gl{Push|Pop}Matrix deprecated in 3.3, roll my own in shader land)
                * 2. transform according to this objects transformations
                * 3. draw encapsulated thing
                * 4. pop it off
                */
        }

        template<typename std::enable_if_t<(DestDim < SrcDim)>::type* = nullptr>
        void draw() const override
        {
                /* steps: (hand-wavy)
                * 1. draw the lower dimension object with our rot, scal, trans
                * 1. render the object using its orientation
                * 2. texture the lower dimensional object with the rendering
                */
        }

private:
        const IDrawable<T, SrcDim>& m_src;
};

} // namespace geometry
} // namespace graphics
} // namespace vngine
