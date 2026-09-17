/*
    LightBase.cpp

    Implementation of an abstract light source.
*/

#include "scene/light/LightBase.hpp"

namespace toxico {
    LightBase::LightBase(const Color3& color, fp_type intensity)
        : color(color),
          intensity(intensity)
    {}

    LightBase::LightBase(const Color3& color)
        : color(color) {}
}
