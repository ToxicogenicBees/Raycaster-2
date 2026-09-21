/*
    main.cpp

    An example of rendering a simple scene.
*/

#include "scene/geometry/SphereGeometry.hpp"
#include "scene/geometry/BoxGeometry.hpp"
#include "scene/light/PointLight.hpp"
#include "rendering/camera/PerspectiveCamera.hpp"
#include "rendering/shader/RecursivePhongShader.hpp"
#include "scene/material/Material.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/geometry/Size.hpp"
#include "io/image/ImageWriter.hpp"
#include "rendering/utility/RenderSettings.hpp"
#include "rendering/Renderer.hpp"
#include "visuals/Color3.hpp"
#include "visuals/Image.hpp"
#include "scene/Scene.hpp"
#include <numbers>

fp_type rads(fp_type degrees) {
    return degrees * std::numbers::pi / 180.0;
}

int main() {
    // Create a scene
    Scene scene;
    scene.ambience.intensity = 0.05;
    scene.ambience.color = {1, 1, 1};

    // Create geometries
    auto sphere_geometry = scene.geometries.insert(SphereGeometry{});
    auto box_geometry = scene.geometries.insert(BoxGeometry{});

    // Create materials
    auto sphere_material = scene.materials.insert({
        MaterialProperties{
            .base_color = Color3(1, 0, 0),
            .metallic = 0.1,
            .roughness = 0.2,
            .ior = 2.3,
        }
    });
    auto box_material = scene.materials.insert({
        MaterialProperties{
            .base_color = Color3(0, 1, 1),
            .roughness = 0.4,
            .ior = 1.5,
        }
    });

    // Add a room (interior of a box) to the scene
    auto [box_handle, box] = scene.objects.emplace(box_material, box_geometry);
    box.transform.translate({-1, 3, -1});
    box.transform.scale(3);

    // Add a sphere to the scene
    auto [sphere_handle, sphere] = scene.objects.emplace(sphere_material, sphere_geometry);
    sphere.transform.translate(Vector3::yAxis());

    // Add a light to the scene
    auto [light_handle, light] = scene.lights.emplace<PointLight>();
    light.transform.translate({-2, 1, 1.5});
    light.transform.lookAt(sphere.transform.position());
    light.properties.attenuation = {0.25, 0.0, 1.0};

    // Create a perspective camera pointing at the sphere.
    PerspectiveCamera camera(rads(90));
    camera.transform.translate({-2, 1, 0});
    camera.transform.lookAt(sphere.transform.position());

    // Render the image
    Renderer renderer;
    const auto image = renderer.render(RenderSettings{
        .scene = scene, 
        .camera = camera,
        .shader = RecursivePhongShader{},
        .render_size = Size{1280, 720},
        .background = Color3(0, 0, 0)
    });

    // Write the image to a file
    ImageWriter writer;
    writer.write("out.png", image);

    return 0;
}
