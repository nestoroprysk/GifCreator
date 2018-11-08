#pragma once
#include <vector>
#include <functional>
#include "IDrawable.hpp"
#include "IMovable.hpp"
#include "IZoomable.hpp"
#include "Color.hpp"
#include "Pixel.hpp"

class Square final : public IDrawable, public IMovable, public IZoomable
{
public:
	void draw(ColorMap&, std::size_t imageCount) const override;
	void gotoCenter() override;
	void moveUp() override;
	void moveDown() override;
	void moveLeft() override;
	void moveRight() override;
	void zoomIn() override;
	void zoomOut() override;

private:
	void addIfUnique(std::vector<Pixel>& dest, Pixel const& v);

private:
	std::vector<Pixel> body_{Pixel{0, 0, BasicColors::green}};
	mutable std::vector<std::function<void(ColorMap&, std::size_t imageCount)>> lazyComputations_;
};
