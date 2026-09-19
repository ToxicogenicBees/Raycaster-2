/*
    Renderer.tpp

    Template implementation of a scene renderer.
*/

#include "rendering/scheduling/batching/JobBatch.hpp"
#include "foundation/math/Vector.hpp"
#include "visuals/filters/ImageFilterSet.hpp"
#include "visuals/filters/ReinhardFilter.hpp"
#include "visuals/filters/sRGBFilter.hpp"
#include <cstdint>

#include <iostream>

namespace toxico {
    template<Shader S>
    Image Renderer::render(const Size& size, const Scene& scene, const CameraBase& camera, const S& shader, const Color4& background) {
        // Update cached transforms
        for (auto& object : scene.objects)
            object.transform.update();
        camera.transform.update();

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

        // Create a job batch to process each scan line.
        JobBatch render_pixels;
        for (std::size_t row = 0; row < size.height; ++row) {
            render_pixels.push([row, size, render_pixel] {
                for (std::size_t col = 0; col < size.width; ++col)
                    render_pixel(row, col);
            });
        }

        // Process each pixel in the image
        auto handle = scheduler_.submit(std::move(render_pixels));
        handle.wait();

        std::clog << "Rendered\n";

        // Filter the image
        ImageFilterSet filters;
        filters.add<ReinhardFilter>();
        filters.add<sRGBFilter>();

        std::clog << "Filtered\n";

        return filters.apply(image);
    }
}