/*
    main.cpp

    An example of rendering a simple scene.
*/

#include "scene/geometry/SphereGeometry.hpp"
#include "scene/geometry/PlaneGeometry.hpp"
#include "scene/light/PointLight.hpp"
#include "rendering/camera/PerspectiveCamera.hpp"
#include "rendering/shaders/LambertianShader.hpp"
#include "rendering/shaders/PhongShader.hpp"
#include "rendering/material/FlatMaterial.hpp"
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
    scene.ambience.intensity = 0.05;
    scene.ambience.color = {1, 1, 1};

    // Create geometries
    auto sphere_geometry = scene.geometries.insert(SphereGeometry{});
    auto plane_geometry = scene.geometries.insert(PlaneGeometry{});

    // Create materials
    auto sphere_material = scene.materials.insert<FlatMaterial>(MaterialSample{
        .ambient = Color3(0.7, 0, 0),
        .diffuse = Color3(1, 0, 0),
        .specular = Color3(1, 1, 1),
        .shininess = 17,
    });
    auto plane_material = scene.materials.insert<FlatMaterial>(MaterialSample{
        .ambient = Color3(0, 0.7, 0.7),
        .diffuse = Color3(0, 1, 1),
        .specular = Color3(0.1, 0.1, 0.1),
        .shininess = 6,
    });

    // Add a floor to the scene
    auto [floor_handle1, floor1] = scene.objects.emplace(plane_material, plane_geometry);

    // Add walls to the scene
    auto [wall_handle2, wall2] = scene.objects.emplace(plane_material, plane_geometry);
    wall2.transform.rotateZ(90 * 3.14159 / 180.0);
    wall2.transform.translate(2 * Vector3::xAxis());
    auto [wall_handle3, wall3] = scene.objects.emplace(plane_material, plane_geometry);
    wall3.transform.rotateX(-90 * 3.14159 / 180.0);
    wall3.transform.translate(2 * Vector3::zAxis());

    // Add a sphere to the scene
    auto [sphere_handle, sphere] = scene.objects.emplace(sphere_material, sphere_geometry);
    sphere.transform.translate(Vector3::yAxis());

    // Add a light to the scene
    auto [light_handle, light] = scene.lights.emplace<PointLight>();
    light.transform.translate({-2, 3, 1.5});
    light.properties.attenuation = {0.25, 0.0, 1.0};

    // Create a perspective camera pointing at the sphere.
    const fp_type fov_90_deg = 90.0 * 3.14159 / 180.0;
    PerspectiveCamera camera(fov_90_deg);
    camera.transform.translate({-2, 1, 0});
    camera.transform.lookAt(sphere.transform.position());

    // Render the image
    Renderer renderer;
    const auto image = renderer.render(
        Size{1280, 720},
        scene, 
        camera,
        PhongShader{},
        Color4(0, 0, 0, 1)
    );

    // Write the image to a file
    ImageWriter writer;
    writer.write("out.png", image);

    return 0;
}
