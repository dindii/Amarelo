#include <Physics/Hittable.h>


class Sphere : public Hittable
{
public:
	Sphere() = delete;
	Sphere(vec3<float>& center, double radius) : m_Center(center), m_Radius(radius) {};

	bool Hit(const Ray& ray, const Interval& bounds, HitRecord& rec) const override;

private:
	vec3<float> m_Center;
	float m_Radius;
};