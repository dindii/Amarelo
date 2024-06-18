#pragma once
#include "Material.h"
#include <Math/vec3.h>

struct HitRecord;
class Ray;

namespace Amrl
{
	class Lambertian : public Material
	{
	public:
		Lambertian(const vec3<float>& albedo) : m_Albedo(albedo) {};

		bool Scatter(const Ray& inputRay, const HitRecord& result, vec3<float>& attenuation, Ray& scatteredRay) const override;

	private:
		vec3<float> m_Albedo;
	};
}
