#pragma once
#include <vector>
#include <functional>
#include "IDrawable.hpp"
#include "IMovable.hpp"
#include "IZoomable.hpp"
#include "IColorable.hpp"

class Square final : public IDrawable, public IMovable, public IZoomable, public IColorable
{
public:
	void draw(Utils::ColorMatrix&, std::size_t imageCount) const override;
	void gotoCenter() override;
	void moveUp() override;
	void moveDown() override;
	void moveLeft() override;
	void moveRight() override;
	void zoomIn() override;
	void zoomOut() override;
	void setColor(Color const&) override;

private:
	using LazyComputationType = std::function<void(Utils::ColorMatrix&, std::size_t imageCount)>;

private:
	std::size_t findCenteredTopLeft(std::size_t dimentionLen) const;
	void addComputation(LazyComputationType&&) const;

private:
	Pixel topLeft_{Pixel{0, 0, BasicColors::white}};
	std::size_t sideLen_ = 1;
	mutable std::vector<LazyComputationType> lazyComputations_;
};
