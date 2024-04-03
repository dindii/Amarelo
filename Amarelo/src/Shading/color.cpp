#include "color.h"
#include <Physics/Shapes/Sphere.h>

#include <Math/generalmath.h>

vec3<uint8_t> Color::CalculateRayColor(const Ray& ray, const HittableList& sceneObjects)
{
	HitRecord result;
	
	if (sceneObjects.Hit(ray, 0, Amrl::g_AmrlInfinity, result))
	{
			vec3<float> normalColor = result.surfaceNormal;
			normalColor = vec3<float>(normalColor.x + 1, normalColor.y + 1, normalColor.z + 1) * 0.5f;
			return ConvertColor(normalColor);
	}
	
	vec3<float> unitDirection = ray.GetDirection().Normalized();
	float gradientPosition = (unitDirection.y + 1.0f) / 2.0f;
	vec3<float> gradientColor = vec3<float>::lerp({ 1.0f, 1.0f, 1.0f }, { 0.5f, 0.7f, 1.0f }, gradientPosition);

	return ConvertColor(gradientColor);
}

vec3<uint8_t> Color::ConvertColor(const vec3<float>& pixelColor)
{
	uint8_t ir = static_cast<uint8_t>(255.999 * pixelColor.r);
	uint8_t ig = static_cast<uint8_t>(255.999 * pixelColor.g);
	uint8_t ib = static_cast<uint8_t>(255.999 * pixelColor.b);

	return { ir, ig, ib };
}