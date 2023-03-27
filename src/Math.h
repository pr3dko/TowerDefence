#pragma once
#include <math.h>

namespace Math
{
	const float Pi = 3.14159265359f;

	inline float RadiansToDegrees(float radians)
	{
		return radians * 180.0f / Pi;
	}

	inline float DegreesToRadians(float degrees)
	{
		return degrees * Pi / 180.0f;
	}

	inline float Sqrt(float x)
	{
		return sqrtf(x);
	}

	inline float Cos(float x)
	{
		return cosf(x);
	}

	inline float Sin(float x)
	{
		return sinf(x);
	}

	inline float Atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	inline float Acos(float x)
	{
		return acosf(x);
	}

	inline float Abs(float x)
	{
		return fabsf(x);
	}

	inline bool NearZero(float x, float epsilon = 0.5f)
	{
		return Math::Abs(x) < epsilon;
	}
}

class Vector2
{
public:
	float x;
	float y;

	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float a, float b) : x(a), y(b) {}

	Vector2& operator+=(const Vector2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2& operator*=(float s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	Vector2& operator/=(float s)
	{
		return (*this) *= 1 / s;
	}

	Vector2 operator-()
	{
		Vector2 result = *this;
		return result *= -1.0f;
	}

	float MagnitudeSquared() const
	{
		return x * x + y * y;
	}

	float Magnitude() const
	{
		return Math::Sqrt(MagnitudeSquared());
	}

	Vector2& Normalize()
	{
		x /= Magnitude();
		y /= Magnitude();
		return *this;
	}

	static Vector2 Normalize(const Vector2& v)
	{
		Vector2 result = v;
		return result.Normalize();
	}

	static float Dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}
};

inline Vector2 operator+(const Vector2& a, const Vector2& b)
{
	Vector2 result = a;
	result += b;
	return result;
}

inline Vector2 operator-(const Vector2& a, const Vector2& b)
{
	Vector2 result = a;
	result -= b;
	return result;
}

inline Vector2 operator*(const Vector2& v, float s)
{
	Vector2 result = v;
	result *= s;
	return result;
}

inline Vector2 operator*(float s, const Vector2& v)
{
	return v * s;
}

inline Vector2 operator/(const Vector2& v, float s)
{
	return v * 1 / s;
}