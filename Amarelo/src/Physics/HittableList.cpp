#include "HittableList.h"


bool HittableList::Hit(const Ray& ray, double rayMin, double rayMax, HitRecord& result) const
{
	HitRecord tempResult;
	bool hitAnything = false;
	
	double closestHit = rayMax;

	for (const std::shared_ptr<Hittable>& object : m_Hittables)
	{
		if (object->Hit(ray, rayMin, rayMax, tempResult))
		{
			hitAnything = true;
			closestHit = tempResult.t;
			result = tempResult;
		}
	}
	
	return hitAnything;

}
