/*
    Object.cpp

    Implementation of a renderable object.
*/

#include "scene/object/Object.hpp"

namespace toxico {
    Object::Object(MaterialHandle material, GeometryHandle geometry)
        : material(material),
          geometry(geometry)
    {}
}
