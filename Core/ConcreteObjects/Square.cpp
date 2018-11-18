#include "Square.hpp"

Square::Square(const std::string& name)
	: name_(name)
	{}

auto Square::getName() const -> const std::string&
{
	return name_;
}

void Square::draw(Type::ColorMatrix& m, std::size_t imageCount) const
{
	for (const auto& computation : lazyComputations_)
		computation(m, imageCount);
	lazyComputations_.clear();
	for (std::size_t i = 0; i < sideLen_; ++i)
		for (std::size_t j = 0; j < sideLen_; ++j)
			if (topLeft_.y + i < m.size() && topLeft_.x + j < m[0].size())
				m[topLeft_.y + i][topLeft_.x + j] = topLeft_.c;
}

void Square::_gotoCenter()
{
	addComputation([this](Type::ColorMatrix& m, std::size_t){
		topLeft_.x = findCenteredTopLeft(m[0].size());
		topLeft_.y = findCenteredTopLeft(m.size());
	});
}

void Square::_moveUp()
{
	addComputation([this](Type::ColorMatrix&, std::size_t){
		--topLeft_.y;
	});
}

void Square::_moveDown()
{
	addComputation([this](Type::ColorMatrix&, std::size_t){
		++topLeft_.y;
	});
}

void Square::_moveLeft()
{
	addComputation([this](Type::ColorMatrix&, std::size_t){
		--topLeft_.x;
	});
}

void Square::_moveRight()
{
	addComputation([this](Type::ColorMatrix&, std::size_t){
		++topLeft_.x;
	});
}

void Square::_zoomIn()
{
	const auto c = [this](Type::ColorMatrix&, std::size_t){
		sideLen_ += 2;
		topLeft_.x -= 1;
		topLeft_.y -= 1;
	};
	lazyComputations_.push_back(c);
}

void Square::_zoomOut()
{
	const auto c = [this](Type::ColorMatrix&, std::size_t){
		sideLen_ -= (sideLen_ < 3) ? 0 : 2;
		topLeft_.x += 1;
		topLeft_.y += 1;
	};
	lazyComputations_.push_back(c);
}

void Square::_setColor(Color const& color)
{
	colors_.push(color);
	const auto c = [this, color](Type::ColorMatrix&, std::size_t){
		topLeft_.c = color;
	};
	lazyComputations_.push_back(c);
}

void Square::_unsetColor(Color const&)
{
	if (!colors_.empty()) colors_.pop();
	if (colors_.empty()) throw std::logic_error("Invalid unset color in empty stack.");
	const auto color = colors_.top();
	const auto c = [this, color](Type::ColorMatrix&, std::size_t){
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
