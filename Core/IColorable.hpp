#pragma once

#include "Color.hpp"

class IColorable
{
public:
	struct setColor;
	struct unsetColor;

public:
	struct setColor{
		unsetColor mirror() const { return unsetColor(); }
		auto get() const { return &IColorable::_setColor; }
	};
	struct unsetColor{
		setColor mirror() const { return setColor(); }
		auto get() const { return &IColorable::_unsetColor; }
	};

protected:
	virtual void _setColor(const Color&) = 0;
	virtual void _unsetColor(const Color&) = 0;
	virtual ~IColorable() {}
};
