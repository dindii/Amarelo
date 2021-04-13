#include "color.h"


vec3<uint8_t> Color::CalculateRayColor(const Ray& ray)
{
	float t = HitSphere(vec3<float>(-1.0f, 0.0f, -1.0f), 0.5f, ray);

	if (t > 0.0f)
		return ConvertColor({ 1.0f, 0.0f, 1.0f });
	

	vec3<float> unitDirection = ray.GetDirection().Normalized();

	float gradientPosition = (unitDirection.y + 1.0f) / 2.0f;

	vec3<float> gradientColor = vec3<float>::lerp({ 1.0f, 1.0f, 1.0f }, { 0.5f, 0.7f, 1.0f }, gradientPosition);
	return ConvertColor(gradientColor);

}

float Color::HitSphere(const vec3<float>& center, float radius, const Ray& ray)
{
	vec3<float> RayOrigin = ray.GetOrigin();
	vec3<float> RayDirection = ray.GetDirection().Normalized();

	float t = vec3<float>::Dot(center - RayOrigin, RayDirection);
	vec3<float> pointVector = RayOrigin + RayDirection * t;

	float y = vec3<float>::Length(center - pointVector);


	if (y < radius)
	{
		float x = sqrt(radius*radius - y * y);
		float p1 = t - x;
		float p2 = t + x;

		return 1.0f;
	}

	return 0.0f;
}

vec3<uint8_t> Color::ConvertColor(const vec3<float>& pixelColor)
{
	uint8_t ir = static_cast<uint8_t>(255.999 * pixelColor.r);
	uint8_t ig = static_cast<uint8_t>(255.999 * pixelColor.g);
	uint8_t ib = static_cast<uint8_t>(255.999 * pixelColor.b);

	return { ir, ig, ib };
}