#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "Color.hpp"
#include "IMovable.hpp"

class Image;
struct GifWriter;
class IDrawable;

class GifCreator
{
private:
	static const std::uint32_t defaultDelay = 10;
	static constexpr auto defaultFileName = "new.gif";
	using IDrawableUP = std::unique_ptr<IDrawable>;
	using ImageUP = std::unique_ptr<Image>;
	using GifWriterUP = std::unique_ptr<GifWriter>;

public:
	GifCreator(std::uint32_t width, std::uint32_t height,
		std::uint32_t delay = defaultDelay, const char* fileName = defaultFileName);
	void registerObject(std::string uniqueName, IDrawableUP);
	template <typename T> void changeObject(std::string name, void (T::*)());
	void makeFrame();
	~GifCreator();

private:
	GifCreator() = delete;

private:
	void updateImage();

private:
	ImageUP image_;
	GifWriterUP writer_;
	std::uint32_t width_;
	std::uint32_t height_;
	std::uint32_t delay_;
	std::size_t imageCount_;
	std::unordered_map<std::string, IDrawableUP> storage_;
	ColorMap pixelMapper_;
};

template <typename T>
void GifCreator::changeObject(std::string name, void (T::*f)())
{
	if (!f) throw std::invalid_argument("Invalid functor");
	const auto o = dynamic_cast<T*>(storage_.at(name).get());
	if (!o) throw std::logic_error("Cannot convert object with the name " + name + " to " + typeid(T).name());
	(o->*f)();
}
