#pragma once

#ifdef DYNAMIC_EXPORTS
#define DYNAMIC_API __declspec(dllexport)
#else 
#define DYNAMIC_API __declspec(dllimport)
#endif

namespace nh
{
	struct DYNAMIC_API point
	{
		float x, y;

		point(float _x, float _y) : x{ _x }, y{ _y }{}
		point operator+ (point p) { return { p.x + x, p.y + y }; }
	};
}