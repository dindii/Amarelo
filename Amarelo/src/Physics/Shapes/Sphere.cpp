#include "Sphere.h"

#include <algorithm>

bool Sphere::Hit(const Ray& ray, const double AABB_min, const double AABB_max, HitRecord& rec) const
{
	vec3<float> RayOrigin = ray.GetOrigin();
	vec3<float> RayDirection = ray.GetDirection().Normalized();

	float t = vec3<float>::Dot(m_Center - RayOrigin, RayDirection);
	vec3<float> pointVector = RayOrigin + RayDirection * t;

	float y = vec3<float>::Length(m_Center - pointVector);

	if (y < m_Radius)
	{
		float x = sqrt(m_Radius * m_Radius - y * y);
		float p1 = t - x;
		float p2 = t + x;

		
		if (p1 > AABB_min && p1 < AABB_max)
			rec.t = p1;
		else if (p2 > AABB_min && p2 < AABB_max)
			rec.t = p2;
		else
			return false;

		
	//	rec.hitLocation = ray.At(rec.t);
		rec.hitLocation = ray.At(rec.t);
		vec3 outwardNormal = (rec.hitLocation - m_Center).Normalized();
		rec.SetFaceNormal(ray, outwardNormal);

		return true;
	}

	return false;
}
