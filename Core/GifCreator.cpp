#include "GifCreator.hpp"
#include "IDrawable.hpp"
#include "INameable.hpp"
#include "GifWriterHandle.hpp"
#include "Image.hpp"
#include "Color.hpp"

GifCreator::GifCreator(std::uint32_t width, std::uint32_t height, std::size_t nbFrames, std::uint32_t delay)
	: image_(std::make_unique<Image>(width, height))
	, width_(width)
	, height_(height)
	, delay_(delay)
	, nbFrames_(nbFrames)
	, pixelMapper_(Type::ColorMatrix(height, std::vector<Color>(width)))
{
	if (width == 0 || height == 0)
		throw std::invalid_argument("Width and height must be greater than zero");
}

void GifCreator::registerObject(Type::INameableUP&& o)
{
	if (objectStorage_.find(o->getName()) != objectStorage_.end())
		throw std::invalid_argument("The object with the name " + o->getName() + " already exists");
	objectStorage_[o->getName()] = Type::IDrawableUP(&dynamic_cast<IDrawable&>(*o));
	o.release();
}

void GifCreator::registerBehaviour(Type::BehaviourUP&& b)
{
	if (behaviourStorage_.find(b->getName()) != behaviourStorage_.end())
		throw std::invalid_argument("The behaviour with the name " + b->getName() + " already exists");
	behaviourStorage_[b->getName()] = std::move(b);
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
	for (const auto& o : objectStorage_)
		(o.second)->draw(pixelMapper_);
	for (std::size_t i = 0; i < height_; ++i)
		for (std::size_t j = 0; j < width_; ++j)
			image_->fillNextPixel(pixelMapper_[i][j]);
}

void GifCreator::setDoBehaviourForAt(const std::string& behaviourName, const std::string& objectName, std::size_t c)
{
	setSpecifiedBehaviourAt(behaviourName, objectName, c, &Behaviour::getDo);
}

void GifCreator::setUndoBehaviourForAt(const std::string& behaviourName, const std::string& objectName, std::size_t c)
{
	setSpecifiedBehaviourAt(behaviourName, objectName, c, &Behaviour::getUndo);
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

void GifCreator::setSpecifiedBehaviourAt(const std::string& behaviourName, const std::string& objectName, std::size_t at, BehaviorGet f)
{
	const auto& o = objectStorage_.at(objectName);
	const auto& bUP = behaviourStorage_.at(behaviourName);
	for (const auto& c : (*bUP.*f)())
		for (const auto& change : c.second)
			changes_[c.first + at].push_back([&o, change]{ change(o); });
}
