#pragma once

#include "core.h"

#include <iostream>

namespace nh
{
	struct Color
	{
		float r, g, b;

		Color() : r{ 0 }, g{ 0 }, b{ 0 } {}
		Color(float r, float g, float b) : r{ r }, g{ g }, b{ b } {}
		Color(DWORD rgb) : r{ (rgb & 0xFF) / 255.f }, g{ (rgb & 0xFF00) / 255.f }, b{ (rgb & 0xFF0000) / 255.f } {}

		Color operator+ (const Color& c) const { return { r + c.r, g + c.g, b + c.b }; }
		Color operator- (const Color& c) const { return { r - c.r, g - c.g, b - c.b }; }
		Color operator* (float s) const { return { r * s, g * s, b * s }; }

		friend std::istream& operator>> (std::istream& stream, Color& c);

		operator DWORD() const { return ToRGB(); }

		DWORD ToRGB() const
		{
			BYTE red = static_cast<BYTE>(r * 255);
			BYTE green = static_cast<BYTE>(g * 255);
			BYTE blue = static_cast<BYTE>(b * 255);
			return red | (green << 8) | (blue << 16);
		}

		static const Color white;
		static const Color black;
		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color cyan;
		static const Color yellow;
		static const Color magenta;
		static const Color orange;
	};
}