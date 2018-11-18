#include "Circle.hpp"

Circle::Circle(const std::string& name)
	: name_(name)
	{}

auto Circle::getName() const -> const std::string&
{
	return name_;
}

void Circle::draw(Type::ColorMatrix&, std::size_t) const
{

}

void Circle::_gotoCenter()
{

}

void Circle::_moveUp()
{

}

void Circle::_moveDown()
{

}

void Circle::_moveLeft()
{

}

void Circle::_moveRight()
{

}

void Circle::_zoomIn()
{

}

void Circle::_zoomOut()
{

}

void Circle::_setColor(Color const&)
{

}

void Circle::_unsetColor(Color const&)
{

}
