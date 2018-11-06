#include "GifCreator.hpp"
#include "gif.h"
#include "Image.hpp"
#include "Color.hpp"

GifCreator::GifCreator(std::uint32_t width, std::uint32_t height, std::uint32_t delay, const char* fileName)
	: image_(std::make_unique<Image>(width, height))
	, writer_(std::make_unique<GifWriter>())
	, width_(width)
	, height_(height)
	, delay_(delay)
{
	GifBegin(writer_.get(), fileName, width, height, delay);
}

void GifCreator::drawBlackAndWhiteFrames()
{
	while (!image_->isComplete())
		image_->fillNextPixel(BasicColors::black);
	GifWriteFrame(writer_.get(), image_->get(), width_, height_, delay_);
	image_->flush();
	while (!image_->isComplete())
		image_->fillNextPixel(BasicColors::white);
	GifWriteFrame(writer_.get(), image_->get(), width_, height_, delay_);
}

GifCreator::~GifCreator()
{
	GifEnd(writer_.get());
}
