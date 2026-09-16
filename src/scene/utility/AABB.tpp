/*
    AABB.tpp

    Template implementation of an axis-alligned bounding box.
*/

namespace toxico {
    template<typename... Points>
        requires (std::same_as<Points, Vector3> && ...)
    AABB::AABB(const Points&... points) noexcept {
        (expand(points), ...);
    }
}
