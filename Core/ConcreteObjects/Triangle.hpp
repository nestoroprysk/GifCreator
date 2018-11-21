#pragma once

#include <vector>
#include <functional>
#include <stack>

#include <Core/INameable.hpp>
#include <Core/IDrawable.hpp>
#include <Core/IPositionable.hpp>
#include <Core/IMovable.hpp>
#include <Core/IZoomable.hpp>
#include <Core/IColorable.hpp>

class Triangle final : public INameable, public IDrawable, public IPositionable, public IMovable, public IZoomable, public IColorable
{
public:
	Triangle(const std::string& name);

public:
	auto getName() const -> const std::string& override;
	void draw(Type::ColorMatrix&, std::size_t imageCount) const override;
	void _gotoCenter() override;
	void _moveUp() override;
	void _moveDown() override;
	void _moveLeft() override;
	void _moveRight() override;
	void _zoomIn() override;
	void _zoomOut() override;
	void _setColor(Color const&) override;
	void _unsetColor(Color const&) override;

private:
	const std::string name_;
};
