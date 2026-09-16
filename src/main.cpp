/*
    main.cpp
*/

#include "foundation/utility/fp_type.hpp"
#include "scene/camera/OrthographicCamera.hpp"
#include "scene/geometry/SphereGeometry.hpp"
#include "scene/objects/Object.hpp"
#include "io/image/ImageWriter.hpp"
#include "visuals/Image.hpp"

int main() {
    // Create a unit sphere at the origin
    SphereGeometry geometry;
    Object sphere(geometry);

    // Create a camera
    const fp_type camera_view_height = 5;
    OrthographicCamera camera(camera_view_height);

    // Translate the camera
    const auto camera_offset = -5 * OrthographicCamera::local_direction;
    camera.transform().translate(camera_offset);

    // Create an image to be rendered to
    const Size render_size(1024, 1024);
    Image image(render_size);
    image.fill(Color4(0, 0, 0, 1));

    // Run a raycast to populate the image
    for (std::size_t x = 0; x < render_size.width; ++x) {
        for (std::size_t y = 0; y < render_size.width; ++y) {
            // Get the pixel being currently viewed through
            const auto pixel = Vector2{
                static_cast<fp_type>(x),
                static_cast<fp_type>(y)
            };

            // Cast a ray through this pixel and check for an intersection
            const auto ray = camera.generateRay(pixel, render_size);
            const auto result = sphere.intersection(ray);

            // Write a pixel if an intersection occurred
            if (result)
                image.at(x, y) = Color4(1, 1, 1, 1);
        }
    }

    // Write the image to a file
    ImageWriter writer;
    writer.write("out.png", image);

    return 0;
}
