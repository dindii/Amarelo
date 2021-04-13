#pragma once
#include <ostream>
#include <sstream>


//Para manter a simplicidade, não vou usar de templates ou classes bases/derivadas.

template<typename T>
struct vec4
{
	vec4<T>(T scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {};
	vec4<T>(const T xx, const T yy, const T zz, const T ww) : x(xx), y(yy), z(zz), w(ww) {};

	std::string ToString() const
	{	
			std::stringstream ss;
			ss << "vec4: (" << x << ", " << y << ", " << z << ", " << w << ")";
			return ss.str();	
	}

	T Dot(const vec4<T>& other)
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}


	//Retornando uma referencia para o proprio objeto a fim de evitar criar novos objetos e podermos com eficiencia
	//juntar uma operação na outra
	vec4<T>& add(const vec4<T>& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	vec4<T>& subtract(const vec4<T>& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	vec4<T>& multiply(const vec4<T>& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;
	}

	vec4<T>& multiply(const T other)
	{
		for (uint8_t x = 0; x < 4; x++)
			elements[x] *= other;

		return *this;
	}

	vec4<T>& divide(const vec4<T>& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;

		return *this;
	}

	
	friend vec4<T> operator+(vec4<T> left, const vec4<T>& right)
	{
		return left.add(right);
	}

	friend vec4<T> operator-(vec4<T> left, const vec4<T>& right)
	{
		return left.subtract(right);
	}

	friend vec4<T> operator*(vec4<T> left, const vec4<T>& right)
	{
		return left.multiply(right);
	}

	friend vec4<T> operator*(vec4<T> left, const T right)
	{
		return left.multiply(right);
	}

	friend vec4<T> operator/(vec4<T> left, const vec4<T>& right)
	{
		return left.divide(right);
	}


	vec4<T>& operator+=(const vec4<T>& other)
	{
		return add(other);
	}
	vec4<T>& operator-=(const vec4<T>& other)
	{
		return subtract(other);
	}
	vec4<T>& operator*=(const vec4<T>& other)
	{
		return multiply(other);
	}
	vec4<T>& operator/=(const vec4<T>& other)
	{
		return divide(other);
	}

	bool operator==(const vec4<T>& other)
	{
		return (x == other.x && y == other.y && z == other.z && w == other.w);
	}

	bool operator!=(const vec4<T>& other)
	{
		return !(*this == other);
	}

	friend std::ostream& operator<<(std::ostream& os, const vec4<T>& vec)
	{
		return os << vec.ToString();
	}

	union {
		struct {
			T x, y, z, w;
		};
		struct {
			T r, g, b, a;
		};
		struct {
			T elements[4];
		};
	};



};
