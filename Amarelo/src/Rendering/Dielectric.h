#pragma once
#include "Material.h"

class Ray;
struct HitRecord;

namespace Amrl
{
	class Dielectric : public Material
	{
	public:
		Dielectric(float refractionIndex) : m_RefractionIndex(refractionIndex) {};

		virtual bool Scatter(const Ray& inputRay, const HitRecord& result, vec3<float>& attenuation, Ray& scatteredRay) const override;
	private:
		float m_RefractionIndex;
	};
}
