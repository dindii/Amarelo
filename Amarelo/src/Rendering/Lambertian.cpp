#include "Lambertian.h"
#include <Physics/Ray.h>
#include <Physics/HitRecord.h>
#include <Math/generalmath.h>

namespace Amrl
{
	bool Lambertian::Scatter(const Ray& inputRay, const HitRecord& result, vec3<float>& attenuation, Ray& scatteredRay) const
	{
		vec3<float> scatteredDirection = result.surfaceNormal + RandomUnitVector();

		if (scatteredDirection.NearZero())
			scatteredDirection = result.surfaceNormal;

		scatteredRay = Ray(result.hitLocation, scatteredDirection);
		attenuation = m_Albedo;
		return true;
	}

}