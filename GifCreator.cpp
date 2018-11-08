#include "GifCreator.hpp"
#include "gif.h"
#include "Image.hpp"
#include "IDrawable.hpp"
#include "Square.hpp"

GifCreator::GifCreator(std::uint32_t width, std::uint32_t height, std::uint32_t delay, const char* fileName)
	: image_(std::make_unique<Image>(width, height))
	, writer_(std::make_unique<GifWriter>())
	, width_(width)
	, height_(height)
	, delay_(delay)
	, imageCount_(0)
	, pixelMapper_(ColorMap(height, std::vector<Color>(width)))
{
	if (width == 0 || height == 0)
		throw std::invalid_argument("Width and height must be greater than zero");
	GifBegin(writer_.get(), fileName, width, height, delay);
}

void GifCreator::registerObject(std::string uniqueName, std::unique_ptr<IDrawable> d)
{
	if (!d) throw std::invalid_argument("Invalid object with the name " + uniqueName);
	if (storage_.find(uniqueName) != storage_.end())
		throw std::invalid_argument("The object with the name " + uniqueName + " already exists");
	storage_[uniqueName] = std::move(d);
}

void GifCreator::makeFrame()
{
	updateImage();
	GifWriteFrame(writer_.get(), image_->get(), width_, height_, delay_);
	image_->flush();
	for (auto& y : pixelMapper_)
		for (auto& x : y)
			x = BasicColors::black;
	++imageCount_;
}

void GifCreator::updateImage()
{
	for (const auto& o : storage_)
		o.second->draw(pixelMapper_, imageCount_);
	for (std::size_t i = 0; i < height_; ++i)
		for (std::size_t j = 0; j < width_; ++j)
			image_->fillNextPixel(pixelMapper_[i][j]);
}

GifCreator::~GifCreator()
{
	GifEnd(writer_.get());
}
