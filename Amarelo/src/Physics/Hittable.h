#pragma once

#include "HitRecord.h"
#include <Physics/Ray.h>

class Hittable
{
public: 
	virtual ~Hittable() = default;
	virtual bool Hit(const Ray& ray, const double AABB_min, const double AABB_max, HitRecord& rec) const = 0;
};