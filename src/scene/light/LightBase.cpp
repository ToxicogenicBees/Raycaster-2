/*
    LightBase.cpp

    Implementation of an abstract light source.
*/

#include "scene/light/LightBase.hpp"

namespace toxico {
    LightBase::LightBase(const LightProperties& properties)
        : properties(properties) {}
}
