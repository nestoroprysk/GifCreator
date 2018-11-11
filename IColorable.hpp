#pragma once
#include "Color.hpp"

class IColorable
{
public:
	virtual void setColor(const Color&) = 0;
	virtual ~IColorable() {}
};
