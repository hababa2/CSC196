#pragma once

#include "Vector2.h"

namespace nh
{
	struct Transform
	{
		Transform() : position{}, rotation{ 0.0f }, scale{ 1.0f }{}
		Transform(const Vector2& position, float rotation = 0, float scale = 1) : 
			position{ position }, rotation{ rotation }, scale{ scale }{}

		Vector2 position;
		float rotation;
		float scale;
	};
}