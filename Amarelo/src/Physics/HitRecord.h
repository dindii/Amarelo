#pragma once

#include <Math/vec3.h>
#include "Ray.h"

struct HitRecord
{
	HitRecord() : hitLocation(0.0f, 0.0f, 0.0f), surfaceNormal(0.0f, 0.0f, 0.0f), t(0.0f) {};
	
	vec3<float> hitLocation;
	vec3<float> surfaceNormal;
	bool frontFace;

	void SetFaceNormal(const Ray& ray, const vec3<float>& outwardNormal);

	double t; 
};