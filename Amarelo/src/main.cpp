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
	viewportProp.imageWidth = 600;
	viewportProp.aspectRatio = 16.0f / 9.0f;
	viewportProp.lookFrom = { 13.0f, 2.0f, 3.0f };
	viewportProp.lookAt = { 0.0f, 0.0f, 0.0f };
	viewportProp.lookUp = { 0.0f, 1.0f, 0.0f };
	viewportProp.fieldOfView = 20.0f;

	Camera camera(viewportProp);

	HittableList sceneObjs;


	Amrl::Material* ground_material = new Lambertian({ 0.5, 0.5, 0.5 });

	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(0, -1000, 0), 1000, ground_material));

	//for (int a = -11; a < 11; a++)
	//{
	//	for (int b = -11; b < 11; b++)
	//	{
	//		float choose_mat = Gen(0.0f, 1.0f);
	//		vec3<float> center(a + 0.9 * Gen(0.0f, 1.0f), 0.2, b + 0.9*Gen(0.0f, 1.0f));
	//
	//		if ((center - vec3<float>(4, 0.2, 0)).Length() > 0.9)
	//		{
	//			Amrl::Material* sphere_material;
	//
	//			if (choose_mat < 0.8)
	//			{
	//				// diffuse
	//				vec3<float> albedo = Random(0.0f, 1.0f) * Random(0.0f, 1.0f);
	//				sphere_material = new Lambertian(albedo);
	//				sceneObjs.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
	//			}
	//			else if (choose_mat < 0.95)
	//			{
	//				// metal
	//				vec3<float> albedo = Random(0.5, 1);
	//				float fuzz = Gen(0.0f, 0.5f);
	//				sphere_material = new Metal(albedo, fuzz);
	//
	//				sceneObjs.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
	//			}
	//			else
	//			{
	//				// glass
	//				sphere_material = new Dielectric(1.5);
	//				sceneObjs.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
	//			}
	//		}
	//	}
	//}

	auto material1 = new Dielectric(1.5);
	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(0, 1, 0), 1.0, material1));

	auto material2 = new Lambertian((0.4, 0.2, 0.1));
	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(-4, 1, 0), 1.0, material2));

	auto material3 = new Metal((0.7, 0.6, 0.5), 0.0);
	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(4, 1, 0), 1.0, material3));

	camera.Render(&sceneObjs);

	//just do speed up iteration times
#if defined(_WIN64)	|| defined(_WIN32)
	ShellExecute(NULL, "open", "resultImage.png", NULL, NULL, SW_SHOWDEFAULT);
#endif

	return 0;
}