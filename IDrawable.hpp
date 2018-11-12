#pragma once
#include "Utils.hpp"

class IDrawable
{
public:
	virtual void draw(Utils::ColorMatrix&, std::size_t imageCount) const = 0;
	virtual ~IDrawable() {}
};
