/*
    render.cpp

    Implementation of a free function that renders a scene with a camera into an image.
*/

#include "rendering/render.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"
#include "visuals/Color4.hpp"
#include <cstdint>

namespace toxico::rendering {
    Image render(const Size& size, const Scene& scene, const CameraBase& camera) {
        // Create an image to be rendered to
        Image image(size);
        image.fill(Color4(0, 0, 0, 0));

        // Run a raycast to populate the image
        for (std::size_t row = 0; row < size.height; ++row) {
            for (std::size_t col = 0; col < size.width; ++col) {
                // Get the pixel being currently viewed through
                const auto pixel = Vector2{
                    static_cast<fp_type>(col) + fp_type{0.5},
                    static_cast<fp_type>(row) + fp_type{0.5}
                };

                // Cast a ray through this pixel and check for an intersection
                const auto ray = camera.generateRay(pixel, size);
                const auto result = scene.intersect(ray);

                // Write a pixel if an intersection occurred
                if (result) {
                    // @TODO: Implement proper phong reflection model
                    const auto obj_color = result->object.color;
                    image.at(row, col) = Color4(
                        obj_color.r, obj_color.g, obj_color.b, 1.0
                    );
                }
            }
        }

        return image;
    }
}
