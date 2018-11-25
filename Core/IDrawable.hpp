#pragma once

#include "Type.hpp"

class IDrawable
{
public:
	virtual void draw(Type::ColorMatrix&) const = 0;
	virtual ~IDrawable() {}
};
