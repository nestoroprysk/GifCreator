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
	makeFrame();
	image_->flush();
	while (!image_->isComplete())
		image_->fillNextPixel(BasicColors::white);
	makeFrame();
}

void GifCreator::drawMovingDot()
{
	for (std::size_t i = 0; i < width_ * height_; ++i){
		image_->flush();
		for (std::size_t j = 0; j < i; ++j)
			image_->fillNextPixel(BasicColors::black);
		image_->fillNextPixel(BasicColors::white);
		while (!image_->isComplete())
			image_->fillNextPixel(BasicColors::black);
		makeFrame();
	}
}

GifCreator::~GifCreator()
{
	GifEnd(writer_.get());
}

void GifCreator::makeFrame()
{
	GifWriteFrame(writer_.get(), image_->get(), width_, height_, delay_);
}
