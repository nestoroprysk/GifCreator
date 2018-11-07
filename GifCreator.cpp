#include "GifCreator.hpp"
#include "gif.h"
#include "Image.hpp"
#include "IDrawable.hpp"

GifCreator::GifCreator(std::uint32_t width, std::uint32_t height, std::uint32_t delay, const char* fileName)
	: image_(std::make_unique<Image>(width, height))
	, writer_(std::make_unique<GifWriter>())
	, width_(width)
	, height_(height)
	, delay_(delay)
	, imageCount_(0)
{
	map_ = ColorMap(height, std::vector<Color>(width));
	GifBegin(writer_.get(), fileName, width, height, delay);
}

void GifCreator::registerObject(std::unique_ptr<IDrawable> d)
{
	storage_.push_back(std::move(d));
}

void GifCreator::makeFrame()
{
	updateImage();
	GifWriteFrame(writer_.get(), image_->get(), width_, height_, delay_);
	image_->flush();
	for (auto& y : map_)
		for (auto& x : y)
			x = BasicColors::black;
	++imageCount_;
}

void GifCreator::updateImage()
{
	for (const auto& o : storage_)
		o->draw(map_, imageCount_);
	for (std::size_t i = 0; i < height_; ++i)
		for (std::size_t j = 0; j < width_; ++j)
			image_->fillNextPixel(map_[i][j]);
}

GifCreator::~GifCreator()
{
	GifEnd(writer_.get());
}
