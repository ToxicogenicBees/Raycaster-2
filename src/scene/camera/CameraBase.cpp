/*
    CameraBase.cpp

    Implementation of an abstract, in-scene camera.
*/

#include "scene/camera/CameraBase.hpp"

namespace toxico {
    CameraBase::CameraBase(const Transform& transform) noexcept
        : transform(transform) {}
}
