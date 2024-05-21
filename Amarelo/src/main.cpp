#include <iostream>
#include "Utils/Image.h"
#include "Math/vec3.h"
#include "Physics/Ray.h"
#include "Rendering/Viewport.h"
#include "Rendering/Camera.h"
#include "Rendering/Viewport.h"
#include <Physics/Shapes/Sphere.h>

//just do speed up dev process
#include <windows.h>

int main()
{
	const float aspectRatio = 16.0f / 9.0f;
	
	//Image
	//const uint32_t imageWidth = 2560;
	const uint32_t imageWidth = 800;
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
	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(0.0f, 0.0f, -1.0f), 0.5f));
	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(0.0f, -100.5f, -1.0f), 100.0f));

	camera.Render(sceneObjs);

	//just do speed up dev process
	ShellExecute(NULL, "open", "resultImage.png", NULL, NULL, SW_SHOWDEFAULT);

	return 0;
}