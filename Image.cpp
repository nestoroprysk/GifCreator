#include "Image.hpp"
#include "Color.hpp"

Image::Image(std::uint32_t width, std::uint32_t height)
	: data_(std::make_unique<std::uint8_t[]>(width * height * rgba_))
	, width_(width)
	, height_(height)
	, pixelsFilled_(0)
	{}

void Image::fillNextPixel(const Color& c)
{
	if (isComplete())
		throw std::runtime_error("fillNextPixel on complete image.");
	data_[pixelsFilled_++] = c.r;
	data_[pixelsFilled_++] = c.g;
	data_[pixelsFilled_++] = c.b;
	data_[pixelsFilled_++] = c.a;
}

uint8_t const* Image::get() const
{
	if (!isComplete())
		throw std::runtime_error("get on incomplete image.");
	return data_.get();
}

bool Image::isComplete() const
{
	return pixelsFilled_ == width_ * height_ * rgba_;
}

void Image::flush()
{
	pixelsFilled_ = 0;
	while (!isComplete())
		fillNextPixel(BasicColors::white);
	pixelsFilled_ = 0;
}
