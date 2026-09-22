/*
    AABB.cpp

    Implementation of an axis-alligned bounding box.
*/

#include "foundation/geometry/AABB.hpp"
#include <algorithm>
#include <cstddef>
#include <limits>

namespace toxico {
    void AABB::expand(const Vector3& point) noexcept {
        if (!min_)
            min_ = point;

        if (!max_)
            max_ = point;

        min_->x = std::min(min_->x, point.x);
        min_->y = std::min(min_->y, point.y);
        min_->z = std::min(min_->z, point.z);

        max_->x = std::max(max_->x, point.x);
        max_->y = std::max(max_->y, point.y);
        max_->z = std::max(max_->z, point.z);
    }

    void AABB::expand(const AABB& bounds) noexcept {
        if (!bounds.boundless()) {
            expand(*bounds.min_);
            expand(*bounds.max_);
        }
    }

    bool AABB::intersects(const Ray3& ray, NumberRange<fp_type> t) const noexcept {
        if (boundless())
            return true;

        for (std::size_t axis = 0; axis < Vector3::degree; ++axis) {
            const fp_type origin = ray.origin[axis];
            const fp_type direction = ray.direction[axis];

            if (std::fabs(direction) < std::numeric_limits<fp_type>::epsilon()) {
                // Ray is parallel to the slab
                if (origin < (*min_)[axis] || origin > (*max_)[axis])
                    return false;

                continue;
            }

            const fp_type inv_d = 1.0 / direction;
            fp_type t0 = ((*min_)[axis] - origin) * inv_d;
            fp_type t1 = ((*max_)[axis] - origin) * inv_d;

            if (t0 > t1)
                std::swap(t0, t1);

            auto t_min = std::max(t.min(), t0);
            auto t_max = std::min(t.max(), t1);
            if (t_min > t_max)
                return false;
        }

        return true;
    }

    bool AABB::intersects(const Ray3& ray) const noexcept {
        return intersects(ray, {fp_type{0.0}, std::numeric_limits<fp_type>::max()});
    }

    Vector3 AABB::lowerBound() const noexcept {
        return min_.value_or(std::numeric_limits<fp_type>::max() * Vector3::one());
    }

    Vector3 AABB::upperBound() const noexcept {
        return max_.value_or(std::numeric_limits<fp_type>::min() * Vector3::one());
    }

    bool AABB::boundless() const noexcept {
        return !min_ || !max_;
    }
}
