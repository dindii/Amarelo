#include "Material.h"

 #include <Physics/Ray.h>
 #include <Physics/HitRecord.h>
 
namespace Amrl
{
	bool Material::Scatter(const Ray& inputRay, const HitRecord& result, vec3<float>& attenuation, Ray& scatteredRay) const
	{
		return false;
	}
}
