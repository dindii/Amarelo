#pragma once

#include "generalmath.h"


class Interval
{
public:
	Interval() : m_Min(+Amrl::g_AmrlInfinity), m_Max(-Amrl::g_AmrlInfinity) {};
	Interval(float min, float max) : m_Min(min), m_Max(max) {};

	inline float Size() const { return (m_Max- m_Min); }

	inline bool Contains(float x) const { return (m_Min <= x && x <= m_Max); }
	inline bool Surrounds(float x) const { return (m_Min < x && x < m_Max); }

	float Clamp(float x) const { return Amrl::clamp<float>(m_Min, m_Max, x); }

	inline const float Max() const { return m_Max; }
	inline const float Min() const { return m_Min; }

private:
	float m_Min, m_Max;
};

extern const Interval g_Empty;
extern const Interval g_Universe;
