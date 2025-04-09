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

//just do speed up iteration times
#if defined(_WIN64)	|| defined(_WIN32)
#include <windows.h>
#endif

using namespace Amrl;

int main()
{	
	ViewportProperties viewportProp;
	viewportProp.imageWidth = 2560;
	viewportProp.aspectRatio = 16.0f / 9.0f;
	viewportProp.lookFrom = { 13.0f, 2.0f, 3.0f };
	viewportProp.lookAt = { 0.0f, 0.0f, 0.0f };
	viewportProp.lookUp = { 0.0f, 1.0f, 0.0f };
	viewportProp.fieldOfView = 20.0f;

	Camera camera(viewportProp);

	HittableList sceneObjs;


	Amrl::Material* ground_material = new Lambertian({ 0.1, 0.1, 0.2 });

	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(0, -1000, 0), 1000, ground_material));


	auto material1 = new Lambertian({ 139.0f / 255, 0.0f, 0.0f });
	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(4, 1, -1), 1.0, material1));
	
	auto material2 = new Lambertian({ (91.f / 255.f), (194.f / 255.f), (231.f / 255.f) });
	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(-4, 1, -1), 1.0, material2));
	
	auto material3 = new Lambertian({(247.f / 255.f), (150 / 255.f), (15.f /255.f)});
	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(0.0, 1, -1), 1.0, material3));

	auto material4 = new Dielectric(1.2f, { 0.4f, 0.0f, 0.35f });
	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(5.0, 0.8, 2.8), 0.8, material4));

	camera.Render(&sceneObjs);

	//just do speed up iteration times
#if defined(_WIN64)	|| defined(_WIN32)
	ShellExecute(NULL, "open", "resultImage.png", NULL, NULL, SW_SHOWDEFAULT);
#endif

	return 0;
}