#include <Physics/Hittable.h>

class Material;

namespace Amrl
{
	class Sphere : public Hittable
	{
	public:
		Sphere() = delete;
		Sphere(vec3<float>& center, float radius, Material* mat) : m_Center(center), m_Radius(radius), m_Mat(mat) {};

		bool Hit(const Ray& ray, const Interval& bounds, HitRecord& rec) const override;

	private:
		vec3<float> m_Center;
		float m_Radius;
		Material* m_Mat;
	};
}