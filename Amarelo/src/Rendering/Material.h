#pragma once
#include <Math/vec3.h>


namespace Amrl
{
	class Ray;
	struct HitRecord;
	
	class Material
	{
	public:
		virtual ~Material() = default;

		virtual bool Scatter(const Ray& inputRay, const HitRecord& result, vec3<float>& attenuation, Ray& scatteredRay) const;
	};
}
