/*
    main.cpp

    An example of rendering a simple scene.
*/

#include "foundation/utility/fp_type.hpp"
#include "scene/geometry/utility/GeometryPrimitives.hpp"
#include "foundation/geometry/Size.hpp"
#include "rendering/camera/PerspectiveCamera.hpp"
#include "rendering/camera/OrthographicCamera.hpp"
#include "rendering/render.hpp"
#include "scene/Scene.hpp"
#include "io/image/ImageWriter.hpp"
#include "visuals/Image.hpp"

int main() {
    // Create a scene
    Scene scene;

    // Add plane to the scene
    auto& plane = scene.createObject(GeometryPrimitives::Plane);
    plane.color = Color3(0, 1, 1);

    // Add a sphere to the scene
    auto& sphere = scene.createObject(GeometryPrimitives::Sphere);
    sphere.transform.translate(Vector3::yAxis());
    sphere.color = Color3(1, 0, 0);

    // Create a perspective camera pointing at the sphere.
    fp_type fov_90_deg = 90.0 * 3.14159 / 180.0;
    PerspectiveCamera camera(fov_90_deg);
    camera.transform.translate({-2, 0.25, 0});
    camera.transform.lookAt(sphere.transform.position());

    // Render the image
    auto image = rendering::render(Size{1720, 1080}, scene, camera);

    // Write the image to a file
    ImageWriter writer;
    writer.write("out.png", image);

    return 0;
}
