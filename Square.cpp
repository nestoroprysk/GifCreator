#include "Square.hpp"
#include <algorithm>

void Square::draw(Utils::ColorMatrix& m, std::size_t imageCount) const
{
	for (const auto& computation : lazyComputations_)
		computation(m, imageCount);
	lazyComputations_.clear();
	for (std::size_t i = 0; i < sideLen_; ++i)
		for (std::size_t j = 0; j < sideLen_; ++j)
			if (topLeft_.y + i < m.size() && topLeft_.x + j < m[0].size())
				m[topLeft_.y + i][topLeft_.x + j] = topLeft_.c;
}

void Square::gotoCenter()
{
	addComputation([this](Utils::ColorMatrix& m, std::size_t){
		topLeft_.x = findCenteredTopLeft(m[0].size());
		topLeft_.y = findCenteredTopLeft(m.size());
	});
}

void Square::moveUp()
{
	addComputation([this](Utils::ColorMatrix&, std::size_t){
		--topLeft_.y;
	});
}

void Square::moveDown()
{
	addComputation([this](Utils::ColorMatrix&, std::size_t){
		++topLeft_.y;
	});
}

void Square::moveLeft()
{
	addComputation([this](Utils::ColorMatrix&, std::size_t){
		++topLeft_.x;
	});
}

void Square::moveRight()
{
	addComputation([this](Utils::ColorMatrix&, std::size_t){
		--topLeft_.x;
	});
}

void Square::zoomIn()
{
	const auto c = [this](Utils::ColorMatrix&, std::size_t){
		sideLen_ += 2;
		topLeft_.x -= 1;
		topLeft_.y -= 1;
	};
	lazyComputations_.push_back(c);
}

void Square::zoomOut()
{
	const auto c = [this](Utils::ColorMatrix&, std::size_t){
		sideLen_ -= (sideLen_ < 3) ? 0 : 2;
		topLeft_.x += 1;
		topLeft_.y += 1;
	};
	lazyComputations_.push_back(c);
}

void Square::setColor(Color const& color)
{
	const auto c = [this, color](Utils::ColorMatrix&, std::size_t){
		topLeft_.c = color;
	};
	lazyComputations_.push_back(c);
}

std::size_t Square::findCenteredTopLeft(std::size_t dimentionLen) const
{
	const auto midDimension = dimentionLen / 2;
	const auto halfVal = sideLen_ / 2;
	return (midDimension > halfVal) ? midDimension - halfVal : 0;
}

void Square::addComputation(LazyComputationType&& c) const
{
	lazyComputations_.push_back(std::move(c));
}
