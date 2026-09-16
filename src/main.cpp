/*
    main.cpp
*/

#include "foundation/utility/fp_type.hpp"
#include "scene/camera/OrthographicCamera.hpp"
#include "foundation/containers/SlotArray.hpp"
#include "scene/geometry/SphereGeometry.hpp"
#include "scene/geometry/GeometryHandle.hpp"
#include "scene/query/intersect.hpp"
#include "scene/object/Object.hpp"
#include "io/image/ImageWriter.hpp"
#include "visuals/Image.hpp"

int main() {
    // Create a sphere geometry (unit sphere at origin)
    SlotArray<IGeometry, GeometryHandle> geometries;
    auto sphere_handle = geometries.insert(std::make_unique<SphereGeometry>());

    // Instantiate a unit sphere at the origin
    Object sphere(sphere_handle);

    // Create a camera looking at the sphere
    const fp_type camera_view_height = 10;
    OrthographicCamera camera(camera_view_height);
    camera.transform.translate(-5 * Vector3::xAxis());
    camera.transform.lookAt(sphere.transform.position());
    
    // Create an image to be rendered to
    const Size render_size(1280, 720);
    Image image(render_size);
    image.fill(Color4(0, 0, 0, 1));

    // Run a raycast to populate the image
    for (std::size_t row = 0; row < render_size.height; ++row) {
        for (std::size_t col = 0; col < render_size.width; ++col) {
            // Get the pixel being currently viewed through
            const auto pixel = Vector2{
                static_cast<fp_type>(col),
                static_cast<fp_type>(row)
            };

            // Cast a ray through this pixel and check for an intersection
            const auto ray = camera.generateRay(pixel, render_size);
            const auto result = intersect(
                *geometries.resolve(sphere.geometry),
                sphere.transform,
                ray
            );

            // Write a pixel if an intersection occurred
            if (result)
                image.at(row, col) = Color4(1, 1, 1, 1);
        }
    }

    // Write the image to a file
    ImageWriter writer;
    writer.write("out.png", image);

    return 0;
}
