#pragma once

#include "Matrix3.h"

namespace nh
{
	struct Transform
	{
		Transform() : position{ 0.0f, 0.0f }, rotation{ 0.0f }, scale{ 1.0f }, lPosition{ 0.0f }, lScale{ 1.0f }, lRotation{ 0.0f }{}
		Transform(const Vector2& position, float rotation = 0, float scale = 1) : 
			position{ position }, rotation{ rotation }, scale{ scale }, lPosition{ 0.0f }, lScale{ 1.0f }, lRotation{ 0.0f }{}

		Matrix33 matrix;
		Vector2 position;
		Vector2 scale;
		float rotation;

		Vector2 lPosition;
		Vector2 lScale;
		float lRotation;

		void Update();
		void Update(const Matrix33& mx);
	};
}