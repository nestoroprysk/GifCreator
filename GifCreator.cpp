#include "GifCreator.hpp"
#include "IDrawable.hpp"
#include "GifWriterHandle.hpp"
#include "Image.hpp"
#include "Color.hpp"

GifCreator::GifCreator(std::uint32_t width, std::uint32_t height, std::size_t nbFrames, std::uint32_t delay)
	: image_(std::make_unique<Image>(width, height))
	, width_(width)
	, height_(height)
	, nbFrames_(nbFrames)
	, delay_(delay)
	, pixelMapper_(Type::ColorMatrix(height, std::vector<Color>(width)))
{
	if (width == 0 || height == 0)
		throw std::invalid_argument("Width and height must be greater than zero");
}

void GifCreator::registerObject(std::unique_ptr<IDrawable>&& o, const std::string& uniqueName){
	if (storage_.find(uniqueName) != storage_.end())
		throw std::invalid_argument("The object with the name " + uniqueName + " already exists");
	storage_[uniqueName] = std::move(o);
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
	setSpecifiedBehaviourAt(at, objectName, b, &Behaviour::getDo);
}

void GifCreator::setUndoBehaviourAt(std::size_t at, const std::string& objectName, const Behaviour& b)
{
	setSpecifiedBehaviourAt(at, objectName, b, &Behaviour::getUndo);
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

void GifCreator::setSpecifiedBehaviourAt(std::size_t at, const std::string& objectName, const Behaviour& b, BehaviorGet f)
{
	const auto& o = storage_.at(objectName);
	for (const auto& c : (b.*f)())
		for (const auto& change : c.second)
			changes_[c.first + at].push_back([&o, change]{ change(o); });
}
