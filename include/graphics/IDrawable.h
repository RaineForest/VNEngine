
#pragma once

#include <graphics/geometry/Point.h>

namespace vngine {
namespace graphics {

using geometry::Point;

/**
 * Interface for describing drawable objects
 */
template<typename T, unsigned int Dim>
class IDrawable
{
public:
        virtual ~IDrawable() = 0;

        /**
         * Draws the object 
         */
        virtual void draw() const = 0;

        /**
         * Sets the location of the object being drawn
         * \param newLoc the new location of the object
         */
        void setLocation(const Point<T, Dim>& newLoc) { m_location = newLoc; }
        
        /**
         * Gets the location of the object being drawn
         * \return the location of the object
         */
        const Point<T, Dim>& getLocation() const { return m_location; }

        /**
         * Sets the orientation of the object being drawn
         * \param newRot the new orientation of the object
         */
        void setOrientation(const Point<T, Dim>& newRot) { m_orientation = newRot; }

        /**
         * Gets the orientation of the object being drawn
         * \return the orientation of the object
         */
        const Point<T, Dim>& getOrientation() const { return m_orientation; }

        /**
         * Sets the scale of the object being drawn
         * \param newRot the new scale of the object
         */
        void setScale(const Point<T, Dim>& newScale) { m_scale = newScale; }

        /**
         * Gets the scale of the object being drawn
         * \return the scale of the object
         */
        const Point<T, Dim>& getOrientation() const { return m_scale; }

protected:
        Point<T, Dim> m_location;
        Point<T, 3>   m_orientation; // rotation, only applicable to 3-space?
        Point<T, Dim> m_scale;
};

} // namespace graphics
} // namespace vngine
