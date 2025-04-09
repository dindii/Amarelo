#pragma once
#include "Material.h"

class Ray;
struct HitRecord;

namespace Amrl
{
	class Dielectric : public Material
	{
	public:
		Dielectric(float refractionIndex, const vec3<float>& color) : m_RefractionIndex(refractionIndex), m_Color(color) {};

		virtual bool Scatter(const Ray& inputRay, const HitRecord& result, vec3<float>& attenuation, Ray& scatteredRay) const override;
	private:
		float m_RefractionIndex;
		vec3<float> m_Color;
	};
}
