#pragma once

namespace nh
{
	struct Vector2
	{
		float x, y;

		Vector2() : x{ 0.0f }, y{ 0.0f }{}
		Vector2(float x, float y) : x{ x }, y{ y }{}
		Vector2(int x, int y) : x{ static_cast<float>(x) }, y{ static_cast<float>(y) }{}

		Vector2 operator+ (const Vector2& v) const { return { x + v.x, y + v.y }; }
		Vector2 operator- (const Vector2& v) const { return { x - v.x, y - v.y }; }
		Vector2 operator* (float s) const { return { x * s, y * s }; }

		Vector2& operator+= (const Vector2& v) { x += v.x; y += v.y; return *this; };
		Vector2& operator-= (const Vector2& v) { x -= v.x; y -= v.y; return *this; };
		Vector2& operator*= (float s) { x *= s; y *= s; return *this; };

		static const Vector2 up;
		static const Vector2 down;
		static const Vector2 left;
		static const Vector2 right;
	};
}