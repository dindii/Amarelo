#pragma once
#include "Utils/Image.h"
#include "Physics/Ray.h"
#include <Physics/HittableList.h>

struct Color
{
	static vec3<uint8_t> CalculateRayColor(const Ray& ray, const HittableList& sceneObjects);
};