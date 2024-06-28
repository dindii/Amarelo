#include <iostream>
#include "Utils/Image.h"
#include "Math/vec3.h"
#include "Physics/Ray.h"
#include "Rendering/Viewport.h"
#include "Rendering/Camera.h"
#include "Rendering/Viewport.h"
#include <Physics/Shapes/Sphere.h>

#include <Rendering/Material.h>
#include <Rendering/Lambertian.h>
#include <Rendering/Metal.h>
#include <Rendering/Dielectric.h>

//just do speed up dev process
#include <windows.h>
using namespace Amrl;

int main()
{
	const float aspectRatio = 16.0f / 9.0f;
	
	//Image
	const uint32_t imageWidth = 2560;
	//const uint32_t imageWidth = 200;
	const uint32_t imageHeight = static_cast<uint32_t>(imageWidth / aspectRatio);

	Image resultImage("resultImage.png", imageWidth, imageHeight, 3);

	//Camera
	//Viewport viewport(2.0f, aspectRatio * 2.0f, 1.0f);
	float focalLength = 1.0f;
	float viewportHeight = 2.0f;
	float viewportWidth = viewportHeight * ((float)imageWidth / (float)imageHeight);

	Viewport viewport(viewportHeight, viewportWidth, 1.0f, imageHeight, imageWidth);
	viewport.AttachOutputImage(&resultImage);
	Camera camera(vec3<float>(0.0f, 0.0f, 0.0f), &viewport);

	HittableList sceneObjs;

	Amrl::Material* material_ground = new Amrl::Lambertian({ 0.8, 0.8, 0.0 });
	Amrl::Material* material_center = new Amrl::Lambertian({ 0.1, 0.2, 0.5 });
	Amrl::Material* material_left = new Amrl::Dielectric(1.50f);
	Amrl::Material* material_right = new Amrl::Metal({ 0.8, 0.6, 0.2 }, 1.0f);
	Amrl::Material* material_middle_right = new Amrl::Metal({ 0.8, 0.6, 0.2 }, 0.01f);

	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(0.0, -100.5, -1.0), 100.0, material_ground));
	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(0.0, 0.0, -1.2), 0.5, material_center));
	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(-1.0, 0.0, -1.0), 0.5, material_left));
	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(1.0, 0.0, -1.0), 0.5, material_right));
	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(0.4, -0.35, -0.8), 0.1, material_middle_right));

	camera.Render(sceneObjs);

	//just do speed up dev process
	ShellExecute(NULL, "open", "resultImage.png", NULL, NULL, SW_SHOWDEFAULT);

	return 0;
}