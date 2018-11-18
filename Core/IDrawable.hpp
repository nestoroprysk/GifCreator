#pragma once

#include "Type.hpp"

class IDrawable
{
public:
	virtual void draw(Type::ColorMatrix&, std::size_t imageCount) const = 0;
	virtual ~IDrawable() {}
};
