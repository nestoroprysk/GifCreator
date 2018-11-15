#pragma once
#include <vector>
#include <functional>
#include <queue>
#include "IDrawable.hpp"
#include "IPositionable.hpp"
#include "IMovable.hpp"
#include "IZoomable.hpp"
#include "IColorable.hpp"

class Square final : public IDrawable, public IPositionable, public IMovable, public IZoomable, public IColorable
{
public:
	void draw(Utils::ColorMatrix&, std::size_t imageCount) const override;
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
	using LazyComputationType = std::function<void(Utils::ColorMatrix&, std::size_t imageCount)>;

private:
	std::size_t findCenteredTopLeft(std::size_t dimentionLen) const;
	void addComputation(LazyComputationType&&) const;

private:
	Pixel topLeft_{Pixel{0, 0, BasicColors::white}};
	std::size_t sideLen_ = 1;
	mutable std::vector<LazyComputationType> lazyComputations_;
private:
	std::queue<Color> colors_;
};
