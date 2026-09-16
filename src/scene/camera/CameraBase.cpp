/*
    CameraBase.cpp

    Implementation of an abstract, in-scene camera.
*/

#include "scene/camera/CameraBase.hpp"

namespace toxico {
    CameraBase::CameraBase(const Transform& transform) noexcept
        : transform_(transform) {}

    const Transform& CameraBase::transform() const noexcept {
        return transform_;
    }
    
    Transform& CameraBase::transform() noexcept {
        return transform_;
    }
}
