#pragma once
#include <ostream>
#include <sstream>

//Para manter a simplicidade, não vou usar de templates ou classes bases/derivadas.

template<typename T>
struct vec3
{
	vec3<T>() = default;
	vec3<T>(T scalar) : x(scalar), y(scalar), z(scalar) {};
	vec3<T>(const T xx, const T yy, const T zz) : x(xx), y(yy), z(zz) {};

	std::string ToString() const
	{
		std::stringstream ss;
		ss << "vec3: (" << x << ", " << y << ", " << z << ")";
		return ss.str();
	}


	T Dot(const vec3<T>& other)
	{
		return x * other.x + y * other.y + z * other.z;
	}

	static float Dot(const vec3& first, const vec3& second)
	{
		return first.x * second.x + first.y * second.y + first.z * second.z;
	}

	static inline vec3<T> Reflect(const vec3<T>& vector, const vec3<T>& normal)
	{
		return vector - 2.0f * Dot(vector, normal) * normal;
	}

	vec3<T> Max(const vec3<T>& other) const
	{
		vec3<T> result;

		for (uint8_t x = 0; x < 3; x++)
			result[x] = elements[x] > other[x] ? elements[x] : other[x];

		return result;
	}

	bool NearZero() const
	{
		double s = 1e-8;
		return (std::fabs(x) < s) && (std::fabs(y) < s) && (std::fabs(z) < s);
	}

	float Max() const
	{
		float maxVal = elements[0];

		for (uint8_t x = 0; x < 3; x++)
			if (elements[x] > maxVal) maxVal = elements[x];

		return maxVal;

	}

	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	float Length2() const
	{
		return (x * x + y * y + z * z);
	}

	static float Length(const vec3& vec)
	{
		return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}
	static float Length2(const vec3& vec)
	{
		return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	static vec3<T> Normalize(const vec3<float>& vec)
	{
		float length = vec3::Length(vec);

		if (length)
			return vec3(vec.x / lenght, vec.y / lenght, vec.z / lenght);

		else
			return vec;	
	}

	vec3<T> Normalized() const
	{
		float length = this->Length();

		if (length)
			return vec3(x / length, y / length, z / length);
		else
			return *this;
		
	}

	static vec3<T> lerp(const vec3& start, const vec3& end, T alpha)
	{
		vec3<T>aux;

		aux.x = (start.x * (1.0f - alpha)) + (end.x * alpha);
		aux.y = (start.y * (1.0f - alpha)) + (end.y * alpha);
		aux.z = (start.z * (1.0f - alpha)) + (end.z * alpha);

		return aux;
	}

	vec3<T> Cross(const vec3& other)
	{
		return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}


	static vec3<T> Cross(const vec3& first, const vec3& second)
	{
		return vec3(first.y * second.z - first.z * second.y,
			first.z * second.x - first.x * second.z,
			first.x * second.y - first.y * second.x);
	}


	//Retornando uma referencia para o proprio objeto a fim de evitar criar novos objetos e podermos com eficiencia
	//juntar uma operação na outra
	vec3<T>& add(const vec3<T>& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	vec3<T>& subtract(const vec3<T>& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	vec3<T> operator-()
	{
		return vec3(-x, -y, -z);
	}

	vec3<T>& multiply(const vec3<T>& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	vec3<T>& multiply(const T other)
	{
		for (uint8_t x = 0; x < 3; x++)
			elements[x] *= other;

		return *this;
	}

	vec3<T>& divide(const vec3<T>& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}


	friend vec3<T> operator+(vec3<T> left, const vec3<T>& right)
	{
		return left.add(right);
	}

	friend vec3<T> operator-(vec3<T> left, const vec3<T>& right)
	{
		return left.subtract(right);
	}

	friend vec3<T> operator*(vec3<T> left, const vec3<T>& right)
	{
		return left.multiply(right);
	}

	friend vec3<T> operator*(vec3<T> left, const T right)
	{
		return left.multiply(right);
	}

	friend vec3<T> operator/(vec3<T> left, const vec3<T>& right)
	{
		return left.divide(right);
	}


	vec3<T>& operator+=(const vec3<T>& other)
	{
		return add(other);
	}
	vec3<T>& operator-=(const vec3<T>& other)
	{
		return subtract(other);
	}
	vec3<T>& operator*=(const vec3<T>& other)
	{
		return multiply(other);
	}
	vec3<T>& operator/=(const vec3<T>& other)
	{
		return divide(other);
	}

	bool operator==(const vec3<T>& other)
	{
		return (x == other.x && y == other.y && z == other.z);
	}

	bool operator!=(const vec3<T>& other)
	{
		return !(*this == other);
	}

	friend std::ostream& operator<<(std::ostream& os, const vec3<T>& vec)
	{
		return os << vec.ToString();
	}

	union {
		struct {
			T x, y, z;
		};
		struct {
			T r, g, b;
		};
		struct {
			T elements[3];
		};
	};



};
