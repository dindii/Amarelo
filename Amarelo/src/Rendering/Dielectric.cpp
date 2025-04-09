#include "Dielectric.h"
#include <Physics/Ray.h>
#include <Physics/HitRecord.h>
#include <Math/generalmath.h>
namespace Amrl
{
	bool Dielectric::Scatter(const Ray& inputRay, const HitRecord& result, vec3<float>& attenuation, Ray& scatteredRay) const
	{
		attenuation = m_Color;

		double refractionIndex = result.frontFace ? (1.0f / m_RefractionIndex) : m_RefractionIndex;

		vec3<float> unitDirection = inputRay.GetDirection().Normalized();
		
		float cosTheta = fmin(vec3<float>::Dot(-unitDirection, result.surfaceNormal), 1.0f);
		float sinTheta = sqrt(1.0f - cosTheta * cosTheta);

		bool cannotRefract = refractionIndex * sinTheta > 1.0f;

		vec3<float> direction;

		if (cannotRefract || Amrl::SchlickReflectance(cosTheta, refractionIndex) > Amrl::Gen(0.0f, 1.0f))
			direction = vec3<float>::Reflect(unitDirection, result.surfaceNormal);
		else
			direction = vec3<float>::Refract(unitDirection, result.surfaceNormal, refractionIndex);

		scatteredRay = Ray(result.hitLocation, direction);

		return true;
	}

}