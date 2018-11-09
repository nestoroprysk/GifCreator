#include "Square.hpp"
#include <algorithm>

void Square::draw(ColorMap& m, std::size_t imageCount) const
{
	for (const auto& computation : lazyComputations_)
		computation(m, imageCount);
	lazyComputations_.clear();
	for (const auto& pixel : body_)
		m[pixel.y % m.size()][(pixel.x) % m[0].size()] = pixel.c;
}

void Square::gotoCenter()
{
	const auto c = [this](ColorMap& m, std::size_t imageCount){
		const auto minY = std::min_element(body_.cbegin(), body_.cend(),
			[](const auto& a, const auto& b) { return a.y < b.y; });
		const auto minX = std::min_element(body_.cbegin(), body_.cend(),
			[](const auto& a, const auto& b) { return a.x < b.x; });
		for (auto& pixel : body_){
			pixel.y -= minY->y;
			pixel.y += m.size() / 2;
			pixel.x -= minX->x;
			pixel.x += m[0].size() / 2;
		}
	};
	lazyComputations_.push_back(c);
}

void Square::moveUp()
{

}

void Square::moveDown()
{

}

void Square::moveLeft()
{

}

void Square::moveRight()
{

}

void Square::zoomIn()
{
	const auto c = [this](ColorMap& m, std::size_t imageCount){
		std::vector<Pixel> newPixels;
		for (const auto& pixel : body_){
			addIfUnique(newPixels, Pixel{pixel.x + 1, pixel.y, pixel.c});
			addIfUnique(newPixels, Pixel{pixel.x + 1, pixel.y + 1, pixel.c});
			addIfUnique(newPixels, Pixel{pixel.x, pixel.y + 1, pixel.c});
			addIfUnique(newPixels, Pixel{pixel.x - 1, pixel.y + 1, pixel.c});
			addIfUnique(newPixels, Pixel{pixel.x - 1, pixel.y, pixel.c});
			addIfUnique(newPixels, Pixel{pixel.x - 1, pixel.y - 1, pixel.c});
			addIfUnique(newPixels, Pixel{pixel.x, pixel.y - 1, pixel.c});
			addIfUnique(newPixels, Pixel{pixel.x + 1, pixel.y - 1, pixel.c});
		}
		body_.insert(std::end(body_), std::begin(newPixels), std::end(newPixels));
	};
	lazyComputations_.push_back(c);
}

void Square::zoomOut()
{

}

void Square::addIfUnique(std::vector<Pixel>& dest, Pixel const& v)
{
	if (std::find(body_.cbegin(), body_.cend(), v) == body_.end())
		dest.push_back(v);
}
