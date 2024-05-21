#include "Camera.h"
#include <Math/generalmath.h>
#include <Utils/Image.h>
#include <iostream>

vec3<float> Camera::RayColor(const Ray& ray, const HittableList& world) const
{
	HitRecord result;

	if (world.Hit(ray, Interval(0, Amrl::g_AmrlInfinity), result))
	{
		vec3<float> normalColor = result.surfaceNormal;
		normalColor = vec3<float>(normalColor.x + 1, normalColor.y + 1, normalColor.z + 1) * 0.5f;
		return normalColor;
		//return Amrl::ConvertColor(normalColor);
	}

	vec3<float> unitDirection = ray.GetDirection().Normalized();
	float gradientPosition = (unitDirection.y + 1.0f) / 2.0f;
	vec3<float> gradientColor = vec3<float>::lerp({ 1.0f, 1.0f, 1.0f }, { 0.5f, 0.7f, 1.0f }, gradientPosition);

	//return Amrl::ConvertColor(gradientColor);
	return gradientColor;
}

void Camera::Render(const HittableList& world) const
{
	Image* outputImg = m_Viewport->GetOutputImage();

	for (int32_t y = outputImg->GetHeight() - 1; y >= 0; y--)
	{
		std::cout << "\rColumns lefting: " << y << ' ' << std::flush;
		for (int32_t x = 0; x < outputImg->GetWidth(); x++)
		{
		
			vec3<float> color = 0;
			
			for (int sample = 0; sample < m_SPP; sample++)
			{
				Ray ray = GenRay(x, y);
				color += RayColor(ray, world);
			}

			outputImg->SetPixel(color  * m_SPPScale);
		}
	}

	

	outputImg->Flush();
	std::cout << "\nDone!" << std::endl;
}


vec3<float> Camera::SampleSquare() const
{
	return vec3<float>(Amrl::Gen<float>(0.0f, 1.0f) - 0.5f, Amrl::Gen<float>(0.0f, 1.0f) - 0.5f, 0.0f);
}

Ray Camera::GenRay(int32_t x, int32_t y) const
{
	vec3<float> randomOffset = SampleSquare();

	vec3<float> rayOrigin = vec3<float>(0.0f, 0.0f, 0.0f);

	vec3<float> sample = m_Viewport->m_FirstPixelLoc + ((x + randomOffset.x) * m_Viewport->m_PixelDeltaU) + ((y + randomOffset.y) * m_Viewport->m_PixelDeltaV);


	vec3<float> rayDir = sample - rayOrigin;
	rayDir = rayDir.Normalized();
	
	return Ray(rayOrigin, rayDir);

}