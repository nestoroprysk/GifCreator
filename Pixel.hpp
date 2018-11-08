#pragma once
#include "Color.hpp"

struct Pixel
{
	std::size_t x = 0;
	std::size_t y = 0;
	Color c;
	bool operator==(Pixel const& rhs) const
		{ return x == rhs.x && y == rhs.y; }
};
