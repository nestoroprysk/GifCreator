#pragma once
#include "Color.hpp"

class IDrawable
{
public:
	virtual void draw(ColorMap&, std::size_t imageCount) const = 0;
	virtual ~IDrawable() {}
};
