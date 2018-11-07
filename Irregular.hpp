#pragma once
#include "IDrawable.hpp"
#include "Pixel.hpp"

struct Irregular final : public IDrawable
{
	Irregular(std::vector<Pixel> const& p) : pixels(p) {}
	void draw(ColorMap&, std::size_t imageCount) const override;
	std::vector<Pixel> pixels;
};
