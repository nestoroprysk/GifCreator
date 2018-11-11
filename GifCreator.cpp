#include "GifCreator.hpp"
#include "IDrawable.hpp"
#include "Square.hpp"
#include "GifWriterHandle.hpp"

GifCreator::GifCreator(std::uint32_t width, std::uint32_t height, std::size_t nbFrames, std::uint32_t delay)
	: image_(std::make_unique<Image>(width, height))
	, width_(width)
	, height_(height)
	, nbFrames_(nbFrames)
	, delay_(delay)
	, pixelMapper_(ColorMap(height, std::vector<Color>(width)))
{
	if (width == 0 || height == 0)
		throw std::invalid_argument("Width and height must be greater than zero");
}

void GifCreator::registerObject(const std::string& uniqueName, IDrawableUP&& d)
{
	if (!d) throw std::invalid_argument("Invalid object with the name " + uniqueName);
	if (storage_.find(uniqueName) != storage_.end())
		throw std::invalid_argument("The object with the name " + uniqueName + " already exists");
	storage_[uniqueName] = std::move(d);
}

void GifCreator::makeFrame(GifWriterHandle& gwh)
{
	updateImage();
	gwh.writeFrame(image_->get());
	image_->flush();
	for (auto& y : pixelMapper_)
		for (auto& x : y)
			x = BasicColors::black;
}

void GifCreator::updateImage()
{
	for (const auto& o : storage_)
		o.second->draw(pixelMapper_, nbFrames_);
	for (std::size_t i = 0; i < height_; ++i)
		for (std::size_t j = 0; j < width_; ++j)
			image_->fillNextPixel(pixelMapper_[i][j]);
}

void GifCreator::createGif(const std::string& fileName)
{
	GifWriterHandle gw(fileName, width_, height_, delay_);
	for (std::size_t i = 0; i < nbFrames_; ++i){
		for (const auto& change : changes_[i])
			change();
		makeFrame(gw);
	}
}
