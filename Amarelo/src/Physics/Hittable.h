#pragma once

#include "HitRecord.h"
#include <Physics/Ray.h>
#include <Math/Interval.h>

class Hittable
{
public: 
	virtual ~Hittable() = default;
	virtual bool Hit(const Ray& ray, const Interval& bounds, HitRecord& rec) const = 0;
};