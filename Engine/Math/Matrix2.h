#pragma once

#include "Vector2.h"

namespace nh
{
	struct Matrix22
	{
		float m[2][2]; //column, row

		Matrix22() : m{ 0.0f, 0.0f, 0.0f, 0.0f } {}
		Matrix22(const Vector2& c1, const Vector2& c2) : m{ c1.x, c1.y, c2.x, c2.y } {}

		void Scale(float s) { m[0][0] = s; m[1][1] = s; m[1][0] = 0.0f; m[0][1] = 0.0f; }
		void Scale(float sx, float sy) { m[0][0] = sx; m[1][1] = sy; m[1][0] = 0.0f; m[0][1] = 0.0f; }
		void Scale(Vector2 s) { m[0][0] = s.x; m[1][1] = s.y; m[1][0] = 0.0f; m[0][1] = 0.0f; }

		void Rotate(float a) { m[0][0] = std::cos(a); m[1][0] = std::sin(a); m[0][1] = -std::sin(a); m[1][1] = std::cos(a); }

		void Identity() { m[0][0] = 1.0f; m[1][1] = 1.0f; m[1][0] = 0.0f; m[0][1] = 0.0f; }

		Matrix22 operator*(const Matrix22& mx) const;
		Vector2 operator*(const Vector2& v) const;
	};

	inline Matrix22 Matrix22::operator*(const Matrix22& mx) const
	{
		Matrix22 r;
		r.m[0][0] = m[0][0] * mx.m[0][0] + m[1][0] * mx.m[0][1];
		r.m[1][0] = m[0][0] * mx.m[1][0] + m[1][0] * mx.m[1][1];
		r.m[0][1] = m[0][1] * mx.m[0][0] + m[1][1] * mx.m[0][1];
		r.m[1][1] = m[0][1] * mx.m[1][0] + m[1][1] * mx.m[1][1];

		return r;
	}

	inline Vector2 Matrix22::operator*(const Vector2& v) const
	{
		Vector2 r;
		r[0] = v[0] * m[0][0] + v[1] * m[0][1];
		r[1] = v[0] * m[1][0] + v[1] * m[1][1];

		return r;
	}
}