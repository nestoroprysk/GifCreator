#include "Triangle.hpp"

Triangle::Triangle(const std::string& name)
	: name_(name)
	{}

auto Triangle::getName() const -> const std::string&
{
	return name_;
}

void Triangle::draw(Type::ColorMatrix&, std::size_t) const
{

}

void Triangle::_gotoCenter()
{

}

void Triangle::_moveUp()
{

}

void Triangle::_moveDown()
{

}

void Triangle::_moveLeft()
{

}

void Triangle::_moveRight()
{

}

void Triangle::_zoomIn()
{

}

void Triangle::_zoomOut()
{

}

void Triangle::_setColor(Color const&)
{

}

void Triangle::_unsetColor(Color const&)
{

}
