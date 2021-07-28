#pragma once

#include <iostream>
#include <cmath>

namespace nh
{
	struct Vector2
	{
		float x, y;

		Vector2() : x{ 0.0f }, y{ 0.0f }{}
		Vector2(float f) : x{ f }, y{ f }{}
		Vector2(float x, float y) : x{ x }, y{ y }{}
		Vector2(int x, int y) : x{ static_cast<float>(x) }, y{ static_cast<float>(y) }{}

		void Set(float _x, float _y) { x = _x; y = _y; }

		float& operator[] (size_t i) { return (&x)[i]; }
		const float operator[] (size_t i) const { return (&x)[i]; }

		Vector2 operator+ (const Vector2& v) const	{ return { x + v.x, y + v.y }; }
		Vector2 operator- (const Vector2& v) const	{ return { x - v.x, y - v.y }; }
		Vector2 operator* (const Vector2& v) const	{ return { x * v.x, y * v.y }; }
		Vector2 operator/ (const Vector2& v) const	{ return { x / v.x, y / v.y }; }
		Vector2 operator+ (float s) const			{ return { x + s, y + s }; }
		Vector2 operator- (float s) const			{ return { x - s, y - s }; }
		Vector2 operator* (float s) const			{ return { x * s, y * s }; }
		Vector2 operator/ (float s) const			{ return { x / s, y / s }; }

		Vector2& operator+= (const Vector2& v)		{ x += v.x; y += v.y; return *this; };
		Vector2& operator-= (const Vector2& v)		{ x -= v.x; y -= v.y; return *this; };
		Vector2& operator*= (const Vector2& v)		{ x *= v.x; y *= v.y; return *this; };
		Vector2& operator/= (const Vector2& v)		{ x /= v.x; y /= v.y; return *this; };
		Vector2& operator+= (float s)				{ x += s; y += s; return *this; };
		Vector2& operator-= (float s)				{ x -= s; y -= s; return *this; };
		Vector2& operator*= (float s)				{ x *= s; y *= s; return *this; };
		Vector2& operator/= (float s)				{ x /= s; y /= s; return *this; };
		
		Vector2 operator - () const					{ return{ -x, -y }; }

		bool operator == (const Vector2& v) const	{ return x == v.x && y == v.y; }
		bool operator != (const Vector2& v) const	{ return x != v.x || y != v.y; }

		friend std::istream& operator>> (std::istream& stream, Vector2& v);

		float Length() const;
		float LengthSqr() const;

		Vector2 Normalized() const;
		void Normalize();

		float Angle() const;
		static float Angle(const Vector2& v1, const Vector2& v2);
		static float SignedAngle(const Vector2& v1, const Vector2& v2);
		static float Dot(const Vector2& v1, const Vector2& v2);

		static float Distance(const Vector2& v1, const Vector2& v2);
		static Vector2 Rotate(const Vector2& v, float radians);

		static const Vector2 up;
		static const Vector2 down;
		static const Vector2 left;
		static const Vector2 right;
		static const Vector2 zero;
		static const Vector2 one;
	};

	inline float Vector2::Length() const		{ return sqrt(x * x + y * y); }
	inline float Vector2::LengthSqr() const		{ return (x * x + y * y); }

	inline Vector2 Vector2::Normalized() const	{ return (*this) * (1 / Length()); }
	inline void Vector2::Normalize()			{ (*this) *= (1 / Length()); }

	inline float Vector2::Angle() const			{ return atan2(y, x); }

	inline float Vector2::Angle(const Vector2& v1, const Vector2& v2) { return acos(Dot(v1, v2)); }

	inline float Vector2::SignedAngle(const Vector2& v1, const Vector2& v2)
	{
		float y = v1.x * v2.y - v1.y * v2.x;
		float x = v1.x * v2.x + v1.y * v2.y;

		return atan2(y, x);
	}

	inline float Vector2::Dot(const Vector2& v1, const Vector2& v2) { return v1.x * v2.x + v1.y * v2.y; }

	inline float Vector2::Distance(const Vector2& v1, const Vector2& v2) { return (v1 - v2).Length(); }

	inline Vector2 Vector2::Rotate(const Vector2& v, float radians) 
	{
		return { v.x * cos(radians) - v.y * sin(radians), v.x * sin(radians) + v.y * cos(radians) };
	}
}