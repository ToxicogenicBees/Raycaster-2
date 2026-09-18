/*
    main.cpp

    An example of rendering a simple scene.
*/

#include "scene/geometry/SphereGeometry.hpp"
#include "scene/geometry/PlaneGeometry.hpp"
#include "rendering/camera/PerspectiveCamera.hpp"
#include "rendering/shaders/FlatShader.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/geometry/Size.hpp"
#include "io/image/ImageWriter.hpp"
#include "rendering/Renderer.hpp"
#include "visuals/Color4.hpp"
#include "visuals/Image.hpp"
#include "scene/Scene.hpp"

int main() {
    // Create a scene
    Scene scene;

    // Create geometries
    auto sphere_geometry = scene.geometries.insert(SphereGeometry{});
    auto plane_geometry = scene.geometries.insert(PlaneGeometry{});

    // Add a plane to the scene
    auto plane_handle = scene.objects.emplace(plane_geometry);
    auto* plane = scene.objects.resolve(plane_handle);
    plane->color = Color3(0, 1, 1);

    // Add a sphere to the scene
    auto sphere_handle = scene.objects.emplace(sphere_geometry);
    auto* sphere = scene.objects.resolve(sphere_handle);
    sphere->transform.translate(Vector3::yAxis());
    sphere->color = Color3(1, 0, 0);

    // Create a perspective camera pointing at the sphere.
    const fp_type fov_90_deg = 90.0 * 3.14159 / 180.0;
    PerspectiveCamera camera(fov_90_deg);
    camera.transform.translate({-2, 0.5, 0});
    camera.transform.lookAt(sphere->transform.position());

    // Render the image
    Renderer renderer;
    const auto image = renderer.render(
        Size{1280, 720},
        scene, 
        camera,
        FlatShader{},
        Color4::transparent()
    );

    // Write the image to a file
    ImageWriter writer;
    writer.write("out.png", image);

    return 0;
}
