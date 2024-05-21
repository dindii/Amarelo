#pragma once

#include "generalmath.h"


class Interval
{
public:
	Interval() : m_Min(+Amrl::g_AmrlInfinity), m_Max(-Amrl::g_AmrlInfinity) {};
	Interval(double min, double max) : m_Min(min), m_Max(max) {};

	inline double Size() const { return (m_Max- m_Min); }

	inline bool Contains(double x) const { return (m_Min <= x && x <= m_Max); }
	inline bool Surrounds(double x) const { return (m_Min < x && x < m_Max); }

	double Clamp(double x) const { return Amrl::clamp<double>(m_Min, m_Max, x); }

	inline const double Max() const { return m_Max; }
	inline const double Min() const { return m_Min; }

private:
	double m_Min, m_Max;
};

extern const Interval g_Empty;
extern const Interval g_Universe;
