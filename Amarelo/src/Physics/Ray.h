#pragma once
#include "Math/vec3.h"

namespace Amrl
{
	class Ray {
	public:
		Ray() = default;
		Ray(const vec3<float>& origin, const vec3<float>& direction)
			: m_Origin(origin), m_Direction(direction.Normalized())
		{}

		inline vec3<float> GetOrigin() const { return m_Origin; }
		inline vec3<float> GetDirection() const { return m_Direction; }

		inline vec3<float> At(float t) const
		{
			return m_Origin + t * m_Direction;
		}

	private:
		vec3<float> m_Origin;
		vec3<float> m_Direction;
	};
}