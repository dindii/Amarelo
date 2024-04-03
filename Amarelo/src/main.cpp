#include <iostream>
#include "Utils/Image.h"
#include "Math/vec3.h"
#include "Shading/color.h"
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
	const uint32_t imageWidth = 2560;
	const uint32_t imageHeight = static_cast<uint32_t>(imageWidth / aspectRatio);

	Image resultImage("resultImage.png", imageWidth, imageHeight, 3);

	//Camera
	Viewport viewport(2.0f, aspectRatio * 2.0f, 1.0f);
	Camera camera(vec3<float>(0.0f), &viewport);

	HittableList sceneObjs;
	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(0.0f, -100.5f, -1.0f), 100.0f));
	sceneObjs.Add(std::make_shared<Sphere>(vec3<float>(0.0f, 0.0f, -1.0f), 0.5f));

	for (int32_t y = imageHeight - 1; y >= 0; y--)
	{
		std::cout << "\rColumns lefting: " << y << ' ' << std::flush;
		for (int32_t x = 0; x < imageWidth; x++)
		{
			float u = (float)x / (imageWidth  - 1);
			float v = (float)y / (imageHeight - 1);

			//Cast a ray from the camera position to the pixel viewport + uv transformation
			Ray ray(camera.GetCameraPosition(), 
				camera.GetCameraViewport().GetAnchorPoint() + u * 
				camera.GetCameraViewport().GetHorizontal()  + v * 
				camera.GetCameraViewport().GetVertical() - camera.GetCameraPosition());

				vec3<uint8_t> finalColor = Color::CalculateRayColor(ray, sceneObjs);
				resultImage.SetPixel(finalColor);
		}
	}

	resultImage.Flush();
	std::cout << "\nDone!" << std::endl;

	//just do speed up dev process
	ShellExecute(NULL, "open", "resultImage.png", NULL, NULL, SW_SHOWDEFAULT);

	return 0;
}