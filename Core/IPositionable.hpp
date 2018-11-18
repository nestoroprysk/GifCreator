#pragma once

class IPositionable
{
public:
	struct gotoCenter;

public:
	struct gotoCenter{
		gotoCenter mirror() const { throw std::logic_error("No mirror function for gotoCenter"); }
		auto get() const { return &IPositionable::_gotoCenter; }
	};

protected:
	virtual void _gotoCenter() = 0;
	virtual ~IPositionable() {}
};
