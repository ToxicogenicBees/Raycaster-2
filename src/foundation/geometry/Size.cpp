/*
    Size.hpp

    Implementation for the Size class
*/

#include "foundation/geometry/Size.hpp"

namespace toxico {
    Size::Size(std::size_t width, std::size_t height)
        : width(width), height(height) {}

    std::size_t Size::area() const {
        return width * height;
    }

    bool Size::operator==(Size size) const {
        return width == size.width
            && height == size.height;
    }

    std::ostream& operator<<(std::ostream& o, Size size) {
        o << "(" << size.width << "x" << size.height << ")";
        return o;
    }
}
