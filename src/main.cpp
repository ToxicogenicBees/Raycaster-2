/*
    main.cpp

    An example of rendering a simple scene.
*/

#include "foundation/utility/fp_type.hpp"
#include "scene/geometry/utility/GeometryPrimitives.hpp"
#include "foundation/geometry/Size.hpp"
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

    // Add sphere to scene
    auto& sphere = scene.createObject(GeometryPrimitives::Sphere);
    sphere.transform.translate(Vector3::yAxis());
    sphere.color = Color3(1, 0, 0);

    // Create a camera looking at the sphere
    OrthographicCamera camera(/*view_height*/ 5);
    camera.transform.translate(-5 * Vector3::xAxis());
    camera.transform.lookAt(sphere.transform.position());

    // Render the image
    auto image = rendering::render(Size{1280, 720}, scene, camera);

    // Write the image to a file
    ImageWriter writer;
    writer.write("out.png", image);

    return 0;
}
