#pragma once

#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Transform.h"

#include <vector>
#include <string>

namespace nh
{
	class Shape
	{
	public:
		Shape() {}
		Shape(const std::vector<Vector2>& points, const Color& color) : points{ points }, color{ color } {}

		void Draw(Core::Graphics& graphics, const Vector2& position, float angle, float scale = 1.0f);
		void Draw(Core::Graphics& graphics, const Transform& transform);

		bool Load(const std::string& filename);

	public:
		std::vector<Vector2> points;
		Color color;
	};
}