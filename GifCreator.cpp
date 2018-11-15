#include "GifCreator.hpp"
#include "IDrawable.hpp"
#include "GifWriterHandle.hpp"
#include "Behaviour.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include "IDrawable.hpp"

GifCreator::GifCreator(std::uint32_t width, std::uint32_t height, std::size_t nbFrames, std::uint32_t delay)
	: image_(std::make_unique<Image>(width, height))
	, width_(width)
	, height_(height)
	, nbFrames_(nbFrames)
	, delay_(delay)
	, pixelMapper_(Utils::ColorMatrix(height, std::vector<Color>(width)))
{
	if (width == 0 || height == 0)
		throw std::invalid_argument("Width and height must be greater than zero");
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
		(o.second)->draw(pixelMapper_, nbFrames_);
	for (std::size_t i = 0; i < height_; ++i)
		for (std::size_t j = 0; j < width_; ++j)
			image_->fillNextPixel(pixelMapper_[i][j]);
}

void GifCreator::setDoBehaviourAt(std::size_t at, const std::string& objectName, const Behaviour& b)
{
	auto* o = storage_.at(objectName).get();
	for (const auto& c : b.getDo())
		for (const auto& change : c.second)
			changes_[c.first + at].push_back([o, change]{ change(o); });
}

void GifCreator::setUndoBehaviourAt(std::size_t at, const std::string& objectName, const Behaviour& b)
{
	auto* o = storage_.at(objectName).get();
	for (const auto& c : b.getUndo())
		for (const auto& change : c.second)
			changes_[c.first + at].push_back([o, change]{ change(o); });
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

GifCreator::~GifCreator(){}
