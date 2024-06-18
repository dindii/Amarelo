#include "Metal.h"
#include <Physics/Ray.h>
#include <Physics/HitRecord.h>
#include <Math/generalmath.h>
namespace Amrl
{
	bool Metal::Scatter(const Ray& inputRay, const HitRecord& result, vec3<float>& attenuation, Ray& scatteredRay) const
	{
		//Get a vector that is the exact reflection of the input vector (over the normal)
		vec3<float> reflected = vec3<float>::Reflect(inputRay.GetDirection(), result.surfaceNormal);

		//Get a Unit random unit vector and add it to the tip of the reflected vector. 
		//If the fuzz value is too high, then this vector that we are adding, will be large as well. The bigger the fuzz, the bigger we will move the reflected vector
		//towards this large random vector (as adding both will retrieve a vector that is halfway between the reflected and the random * fuzz).
		reflected = reflected.Normalized() + (m_Fuzz * Amrl::RandomUnitVector());

		//create an output ray based on that
		scatteredRay = Ray(result.hitLocation, reflected);

		//retrieve diffuse color
		attenuation = m_Albedo;

		//We will Dot product the (Reflected + Random) = (Scattered Ray) with the normal of the surface. This way we can check if this random vector
		//made the reflection vector to be towards the object itself (i.g: made the reflection vector to be inside our sphere).
		//If it is the case, then we will just absorb this color, by returning zero.
		return (vec3<float>::Dot(scatteredRay.GetDirection(), result.surfaceNormal) > 0.0f);
	}

}