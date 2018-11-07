#include "Irregular.hpp"

void Irregular::draw(ColorMap& m, std::size_t imageCount) const
{
	for (const auto& e : pixels)
		m[e.y % m.size()][(e.x + imageCount) % m[0].size()] = e.c;
}
