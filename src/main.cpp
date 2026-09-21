/*
    main.cpp

    An example of rendering a simple scene.
*/

#include "scene/geometry/SphereGeometry.hpp"
#include "scene/geometry/PlaneGeometry.hpp"
#include "scene/light/PointLight.hpp"
#include "rendering/camera/PerspectiveCamera.hpp"
#include "rendering/texture/TextureLoader.hpp"
#include "rendering/shader/PhongShader.hpp"
#include "rendering/material/Material.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/geometry/Size.hpp"
#include "io/image/ImageWriter.hpp"
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
    auto plane_geometry = scene.geometries.insert(PlaneGeometry{});

    // Create materials
    auto sphere_material = scene.materials.insert({
        MaterialProperties{
            .base_color = Color3(1, 0, 0),
            .metallic = 0.1,
            .roughness = 0.2,
            .ior = 2.3,
        }
    });
    auto plane_material = scene.materials.insert({
        MaterialProperties{
            .base_color = Color3(0, 1, 1),
            .roughness = 0.4,
            .ior = 1.5,
        }
    });

    // Add a floor to the scene
    auto [floor_handle, floor] = scene.objects.emplace(plane_material, plane_geometry);

    // Add walls to the scene
    auto [wall_handle1, wall1] = scene.objects.emplace(plane_material, plane_geometry);
    wall1.transform.translate(2 * Vector3::xAxis());
    wall1.transform.rotateZ(rads(90));

    auto [wall_handle2, wall2] = scene.objects.emplace(plane_material, plane_geometry);
    wall2.transform.translate(2 * Vector3::zAxis());
    wall2.transform.rotateX(rads(-90));

    auto [wall_handle3, wall3] = scene.objects.emplace(plane_material, plane_geometry);
    wall3.transform.translate(-4 * Vector3::xAxis());
    wall3.transform.rotateZ(rads(-90));

    auto [wall_handle4, wall4] = scene.objects.emplace(plane_material, plane_geometry);
    wall4.transform.translate(-4 * Vector3::zAxis());
    wall4.transform.rotateX(rads(90));

    // Add a ceiling to the scene
    auto [ceiling_handle, ceiling] = scene.objects.emplace(plane_material, plane_geometry);
    ceiling.transform.translate(6 * Vector3::yAxis());
    ceiling.transform.rotateX(rads(180));

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
    const auto image = renderer.render(
        Size{1280, 720},
        scene, 
        camera,
        PhongShader{},
        Color3(0, 0, 0)
    );

    // Write the image to a file
    ImageWriter writer;
    writer.write("out.png", image);

    return 0;
}
