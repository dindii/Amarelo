#pragma once
#include "Material.h"

class Ray;
struct HitRecord;

namespace Amrl
{
	class Metal : public Material
	{
	public:
		Metal(const vec3<float>& albedo, float fuzz) : m_Albedo(albedo), m_Fuzz(fuzz) {};

		virtual bool Scatter(const Ray& inputRay, const HitRecord& result, vec3<float>& attenuation, Ray& scatteredRay) const override;
	private:
		vec3<float> m_Albedo;
		float m_Fuzz;
	};
}
