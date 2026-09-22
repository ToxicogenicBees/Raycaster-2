/*
    Renderer.tpp

    Template implementation of a scene renderer.
*/

#include "rendering/scheduling/batching/JobBatch.hpp"
#include "foundation/math/Vector.hpp"
#include "visuals/filters/ImageFilterSet.hpp"
#include "visuals/filters/ReinhardFilter.hpp"
#include "visuals/filters/LinearToSRGBFilter.hpp"
#include <cstdint>

namespace toxico {
    template<Shader S>
    Image Renderer::render(const RenderSettings<S>& settings) {
        // Create an image to be rendered to
        Image image(settings.render_size);

        // Helper to render a pixel on screen
        auto render_pixel = [&](std::size_t row, std::size_t col) {
            // Fetch the location this ray will be cast out the camera from
            const Vector2 ray_position{
                static_cast<fp_type>(col + 0.5),
                static_cast<fp_type>(row + 0.5)
            };

            // Generate a ray from the camera through this pixel
            const auto ray = settings.camera.generateRay(ray_position, settings.render_size);

            // Fill the image with the color fetched by the shader through this ray.
            const auto color = settings.shader.shade(ray, settings.scene, settings.background);
            image.at(row, col) = color;
        };

        // Create a job batch to process each scan line.
        JobBatch render_pixels;
        for (std::size_t row = 0; row < settings.render_size.height; ++row) {
            render_pixels.push([row, &settings, render_pixel] {
                for (std::size_t col = 0; col < settings.render_size.width; ++col)
                    render_pixel(row, col);
            });
        }

        // Process each pixel in the image
        auto handle = scheduler_.submit(std::move(render_pixels));
        handle.wait();

        // Filter the image
        ImageFilterSet filters;
        filters.add<ReinhardFilter>();
        filters.add<LinearToSRGBFilter>();
        filters.apply(image);
        
        return image;
    }
}
