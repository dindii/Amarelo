#pragma once

struct Viewport
{
public:
	Viewport(const float height, const float width, const float depth)
		: m_Vertical({ 0.0f, height, 0.0f }), m_Horizontal({ width, 0.0f, 0.0f }), m_Depth({ 0.0f, 0.0f, depth }) {};

	Viewport() : m_Vertical(0.0f), m_Horizontal(0.0f), m_Depth(0.0f) {};

	inline vec3<float> GetVertical() const { return m_Vertical; }
	inline vec3<float> GetHorizontal()  const { return m_Horizontal;  }
	inline vec3<float> GetDepth()  const { return m_Depth;  }
	inline vec3<float> GetAnchorPoint() const { return m_AnchorPoint; }
	inline void SetAnchorPoint(const vec3<float> origin) { m_AnchorPoint = origin - (m_Horizontal / 2) - (m_Vertical / 2) - m_Depth; }



private:
	vec3<float> m_AnchorPoint;
	vec3<float> m_Vertical;
	vec3<float> m_Horizontal;
	vec3<float> m_Depth;
};