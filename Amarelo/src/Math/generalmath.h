#pragma once
#include <stdint.h>
#include <cmath>
#include <limits>
#include <Math/vec3.h>
#include <random>

namespace Amrl
{

	const double g_AmrlPI = 3.1415926535897932385;
	const double g_AmrlInfinity = std::numeric_limits<double>::infinity();

	template<typename T>
	inline T Gen(T min, T max)
	{
		static std::uniform_real_distribution<T> dist(min, max);
		static std::mt19937 generator;

		return static_cast<T>(dist(generator));
	}

	inline vec3<uint8_t> ConvertColor(const vec3<float>& pixelColor)
	{
		uint8_t ir = static_cast<uint8_t>(255.999 * pixelColor.r);
		uint8_t ig = static_cast<uint8_t>(255.999 * pixelColor.g);
		uint8_t ib = static_cast<uint8_t>(255.999 * pixelColor.b);

		return { ir, ig, ib };
	}

	template<typename T> 
	inline int clamp(const T min, const T max, const T val)
	{
		T aux = 0;

		if (val < min)
		{
			aux = min;
			return aux;
		}
		else if (val > max)
		{
			aux = max;
			return aux;
		}

		return val;
	}

	inline uint8_t floatToByte(const float f)
	{
		return (f >= 1.0f ? 255 : (f <= 0.0f ? 0 : (int)floor(f * 256.0f)));
	}

	inline float normalizeInRange(float val, float max, float min)
	{
		return (val - min) / (max - min);
	}

	inline float toDegrees(const float radians)
	{
		return (float)(radians * (180.0f / g_AmrlPI));
	}

	inline float toRadians(const float degrees)
	{
		return (float)(degrees * (g_AmrlPI / 180.0f));
	}

	inline float tan(const float angle)
	{
		return ::tan(angle);
	}

	inline float cos(const float angle)
	{
		return ::cos(angle);
	}

	inline float sin(const float angle)
	{
		return ::sin(angle);
	}

	inline float lerp(const float start, const float end, float alpha)
	{
		return ((start * (1.0f - alpha)) + (end * alpha));
	}

	inline float floorf(const float val)
	{
		return ::floorf(val);
	}

	inline float fabsf(const float val)
	{
		return ::fabsf(val);
	}

	inline float roundf(const float val)
	{
		return ::roundf(val);
	}

	//distance from an integer
	inline float dti(float val)
	{
		return fabsf(val - roundf(val));
	}
	//Module for doubles
	template<typename T, typename U>
	constexpr double dmod(T x, U mod)
	{
		return !mod ? x : x - mod * static_cast<long long>(x / mod);
	}
}


