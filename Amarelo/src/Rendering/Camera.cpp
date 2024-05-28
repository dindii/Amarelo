#include "Camera.h"
#include <Math/generalmath.h>
#include <Utils/Image.h>
#include <iostream>

vec3<float> Camera::RayColor(const Ray& ray, uint32_t maxBounces, const HittableList& world) const
{
	if (maxBounces <= 0)
		return { 0.0f }; 

	HitRecord result;


	//If we hit something, we will bounce once again. This will happens until we reach the sky (i.e: hitting nothing). If we reach the sky, we will take the sky color (let's say, {1.0f, 1.0f, 1.0f}) and return it. Every return divides the result by half. 
	//This simulates that the ray is losing energy on each bounce. So for every return (i.e: bounces) we halve the result. Rays that bounce once and then go straight up, are the ones that have the lowest number of halves, thus the brighter pixels.
	//If we fail to hit something and reach the max bounce count, we will just return the color of the maxBounce, in our case, black. We will just halve the black and at the end the pixel is going to be black, this is rare though, eventually they always get up to the sky
	//so even if it takes many bounces, we will just return a gray or dark gray (after halving many times).
	//The return default color (maxBounces <= 0) doesn't matter much here, because after too many halves (when we exceed a high number eventually) will make the color always closer to black. So even if you select a bright white, it will end up as being black or very close to it.
	//A way to confirm this is to reduce the number of bounces and select a custom color. If you select, for instance, a Purple and select 2 bounces, eventually we will get rays that can't reach the sky and they will be halved at most two times. By only halving 2x we still can see that it is purple,
	//although being a darker version of the original purple (because of the halves).
	if (world.Hit(ray, Interval(0.001, Amrl::g_AmrlInfinity), result))
	{
		vec3 dir = result.surfaceNormal + Amrl::RandomOnHemisphere(result.surfaceNormal);
		return 0.5f * RayColor(Ray(result.hitLocation, dir), (maxBounces - 1), world);
	}

		vec3<float> unitDirection = ray.GetDirection().Normalized();
		float gradientPosition = (unitDirection.y + 1.0f) / 2.0f;
		vec3<float> gradientColor = vec3<float>::lerp({ 1.0f, 1.0f, 1.0f }, { 0.5f, 0.7f, 1.0f }, gradientPosition);
	
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
				color += RayColor(ray, m_MaxBounces, world);
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