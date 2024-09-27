#pragma once
#include <stdint.h>
#include <cmath>
#include <limits>
#include <Math/vec3.h>
#include <random>

namespace Amrl
{

	const float g_AmrlPI = 3.1415926f;
	const float g_AmrlInfinity = std::numeric_limits<float>::infinity();

	inline float LinearToGama(float linear)
	{
		if(linear > 0)
			return sqrt(linear);

		return 0;
	}

	static float SchlickReflectance(float cosine, float refractionIndex)
	{
		float r0 = (1 - refractionIndex) / (1 + refractionIndex);

		r0 = r0 * r0;

		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}

	template<typename T>
	inline T Gen(T min, T max)
	{
		return min + (max - min) * (rand() / (RAND_MAX + 1.0));
	}

	inline vec3<float> Random(float min, float max)
	{
		float x = Gen<float>(min, max);
		float y = Gen<float>(min, max);
		float z = Gen<float>(min, max);
		
		return { x, y, z };
	}

	inline vec3<float> RandomInUnitSphere()
	{
		while (true)
		{
			vec3 point = Random(-1.0f, 1.0f);
			
			if (point.Length2() < 1.0f)
				return point;
		}
	}

	inline vec3<float> RandomInUnitDisk()
	{
		vec3<float> sphere = RandomInUnitSphere();
		return { sphere.x, sphere.y, 0.0f };
	}

	inline vec3<float> RandomUnitVector()
	{
		return RandomInUnitSphere().Normalized();
	}

	inline vec3<float> RandomOnHemisphere(const vec3<float>& normal)
	{
		vec3 onUnitSphere = RandomUnitVector();

		if (vec3<float>::Dot(onUnitSphere, normal) > 0.0f)
			return onUnitSphere;

		return -onUnitSphere;
	}

	inline vec3<uint8_t> ConvertColor(const vec3<float>& pixelColor)
	{
		uint8_t ir = static_cast<uint8_t>(255.999 * pixelColor.r);
		uint8_t ig = static_cast<uint8_t>(255.999 * pixelColor.g);
		uint8_t ib = static_cast<uint8_t>(255.999 * pixelColor.b);

		return { ir, ig, ib };
	}

	template<typename T> 
	inline T clamp(const T min, const T max, const T val)
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
		return (float)(degrees * g_AmrlPI / 180.0f);
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
	//Module for floats
	template<typename T, typename U>
	constexpr float dmod(T x, U mod)
	{
		return !mod ? x : x - mod * static_cast<long long>(x / mod);
	}
}


