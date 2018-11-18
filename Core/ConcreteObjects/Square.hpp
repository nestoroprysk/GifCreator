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

class Square final : public INameable, public IDrawable, public IPositionable, public IMovable, public IZoomable, public IColorable
{
public:
	Square(const std::string& name);

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
	using LazyComputationType = std::function<void(Type::ColorMatrix&, std::size_t imageCount)>;

private:
	std::size_t findCenteredTopLeft(std::size_t dimentionLen) const;
	void addComputation(LazyComputationType&&) const;

private:
	Pixel topLeft_{Pixel{0, 0, BasicColors::white}};
	std::size_t sideLen_ = 1;
	mutable std::vector<LazyComputationType> lazyComputations_;

private:
	std::stack<Color> colors_;

private:
	const std::string name_;
};
