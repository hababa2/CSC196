#include "Vector2.h"

#include <string>

namespace nh
{
	const Vector2 Vector2::up	{  0.0f, -1.0f };
	const Vector2 Vector2::down	{  0.0f,  1.0f };
	const Vector2 Vector2::left	{ -1.0f,  0.0f };
	const Vector2 Vector2::right{  1.0f,  0.0f };
	const Vector2 Vector2::zero	{  0.0f,  0.0f };
	const Vector2 Vector2::one	{  1.0f,  1.0f };

	std::istream& operator>>(std::istream& stream, Vector2& v)
	{
		std::string line;
		std::getline(stream, line);

		if (line.find("{", 0) != std::string::npos)
		{
			int p1 = line.find('{');
			int p2 = line.find(',');

			std::string x = line.substr(p1 + 1, p2 - p1 - 1);
			std::string y = line.substr(p2 + 1, line.find('}') - p2 - 1);

			v.x = std::stof(x);
			v.y = std::stof(y);
		}

		return stream;
	}
}