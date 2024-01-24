#pragma once
#include "Utils/Image.h"
#include "Physics/Ray.h"

struct Color
{
	static vec3<uint8_t> CalculateRayColor(const Ray& ray);
	static float HitSphere(const vec3<float>& center, float radius, const Ray& ray);
	static vec3<uint8_t> ConvertColor(const vec3<float>& pixelColor);
};