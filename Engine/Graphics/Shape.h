#pragma once

#include "../Math/Vector2.h"
#include "../Math/Color.h"

#include <vector>

namespace nh
{
	class Shape
	{
	public:
		Shape() {}
		Shape(const std::vector<Vector2>& points, const Color& color) : points{ points }, color{ color } {}

		void Draw(Core::Graphics& graphics, Vector2 position, float scale = 1.0f);

	private:
		std::vector<Vector2> points;
		Color color;
	};
}