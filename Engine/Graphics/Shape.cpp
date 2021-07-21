#include "Shape.h"
#include "Math\MathUtils.h"

#include <fstream>

namespace nh
{
	void Shape::Draw(Core::Graphics& graphics, const Vector2& position, float angle, float scale)
	{
		graphics.SetColor(color);

		for (size_t i = 0; i < points.size() - 1; i++)
		{
			Vector2 p1 = position + (Vector2::Rotate(points[i], angle) * scale);
			Vector2 p2 = position + (Vector2::Rotate(points[i+1], angle) * scale);

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Shape::Draw(Core::Graphics& graphics, const Transform& transform)
	{
		graphics.SetColor(color);

		for (size_t i = 0; i < points.size() - 1; i++)
		{
			Vector2 p1 = transform.position + (Vector2::Rotate(points[i], transform.rotation) * transform.scale);
			Vector2 p2 = transform.position + (Vector2::Rotate(points[i + 1], transform.rotation) * transform.scale);

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	bool Shape::Load(const std::string& filename)
	{
		std::ifstream stream(filename);
		if (!stream.is_open()) { return false; }

		stream >> color;

		std::string line;
		std::getline(stream, line);
		size_t count = std::stoi(line);

		for (size_t i = 0; i < count; i++)
		{
			Vector2 v;
			stream >> v;

			points.push_back(v);
		}

		ComputeRadius();

		return true;
	}

	void Shape::ComputeRadius()
	{
		for (auto& point : points)
		{
			radius = nh::Max(point.Length(), radius);
		}
	}
}

