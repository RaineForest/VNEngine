
#include "graphics/geometry/Projector.h"

namespace vngine {
namespace graphics {
namespace geometry {

template<typename T, unsigned int DestDim, unsigned int SrcDim>
Projector::Projector(IDrawable<T, SrcDim>& src) :
        m_src(src)
{
}

template<typename T, unsigned int DestDim, unsigned int SrcDim>
Projector::~Projector()
{
}

// if DestDim == SrcDim, then nothing needs to be done, just draw the damn thing
template<typename T, unsigned int DestDim, unsigned int SrcDim, typename = std::enable_if_t<DestDim == SrcDim>::value>
void draw()
{
        m_src.draw();
}

// if DestDim > SrcDim, lift the object into higher dimensional space
template<typename T, unsigned int DestDim, unsigned int SrcDim, typename = std::enable_if_t<DestDim > SrcDim>::value>
void draw()
{
        /* steps:
         * 1. push a transformation matrix (gl{Push|Pop}Matrix deprecated in 3.3, roll my own in shader land)
         * 2. transform according to this objects transformations
         * 3. draw encapsulated thing
         * 4. pop it off
         */
}

// if DestDim < SrcDim, project the object into lower dimensional space
template<typename T, unsigned int DestDim, unsigned int SrcDim, typename = std::enable_if_t<DestDim < SrcDim>::value>
void draw()
{
        /* steps: (hand-wavy)
         * 1. draw the lower dimension object with our rot, scal, trans
         * 1. render the object using its orientation
         * 2. texture the lower dimensional object with the rendering
         */
}

} // namespace geometry
} // namespace graphics
} // namespace vngine
