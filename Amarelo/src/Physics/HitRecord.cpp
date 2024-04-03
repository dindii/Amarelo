#include "HitRecord.h"
#include "Ray.h"

void HitRecord::SetFaceNormal(const Ray& ray, const vec3<float>& outwardNormal)
{
	frontFace = ray.GetDirection().Dot(outwardNormal)  < 0.0f;
	surfaceNormal = frontFace ? outwardNormal : vec3(-outwardNormal.x, -outwardNormal.y, -outwardNormal.z);
}

