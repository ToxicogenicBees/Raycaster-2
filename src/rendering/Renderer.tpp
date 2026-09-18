/*
    Renderer.tpp

    Template implementation of a scene renderer.
*/

#include "foundation/math/Vector.hpp"
#include <cstdint>

namespace toxico {
    template<Shader S>
    Image Renderer::render(const Size& size, const Scene& scene, const CameraBase& camera, const S& shader, const Color4& background) {
        // Create an image to be rendered to
        Image image(size);

        // Helper to render a pixel on screen
        auto render_pixel = [&](std::size_t row, std::size_t col) {
            // Fetch the location this ray will be cast out the camera from
            const Vector2 ray_position{
                static_cast<fp_type>(col + 0.5),
                static_cast<fp_type>(row + 0.5)
            };

            // Generate a ray from the camera through this pixel
            const auto ray = camera.generateRay(ray_position, size);

            // Fill the image with the color fetched by the shader through this ray.
            const auto color = shader.shade(ray, scene, background);
            image.at(row, col) = color;
        };

        // Run a raycast to populate the image
        for (std::size_t row = 0; row < size.height; ++row) {
            for (std::size_t col = 0; col < size.width; ++col) {
                // Render this pixel.
                // @TODO: Thread per-pixel rendering.
                render_pixel(row, col);
            }
        }

        return image;
    }
}