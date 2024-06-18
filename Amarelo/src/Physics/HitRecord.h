#pragma once

#include <Math/vec3.h>


namespace Amrl
{
	class Material;
	class Ray;

	struct HitRecord
	{
		HitRecord() : hitLocation(0.0f, 0.0f, 0.0f), surfaceNormal(0.0f, 0.0f, 0.0f), t(0.0f) {};
		
		Material* mat;
		vec3<float> hitLocation;
		vec3<float> surfaceNormal;
		bool frontFace;
	
		void SetFaceNormal(const Ray& ray, const vec3<float>& outwardNormal);
	
		float t; 
	};
}