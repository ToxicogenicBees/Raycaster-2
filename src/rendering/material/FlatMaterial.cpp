/*
    FlatMaterial.cpp

    Implementation of a flat-colored material.
*/

#include "rendering/material/FlatMaterial.hpp"

namespace toxico {
    FlatMaterial::FlatMaterial(const MaterialSample& sample) noexcept
        : sample_(sample) {}
    
    MaterialSample FlatMaterial::sample(const Vector2& uv) const noexcept {
        return sample_;
    }
}
