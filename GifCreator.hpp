#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <functional>
#include "Color.hpp"
#include "Image.hpp"

class GifWriterHandle;
class IDrawable;

class GifCreator
{
private:
	static const std::uint32_t defaultDelay = 10;
	static constexpr auto defaultFileName = "new.gif";
	using IDrawableUP = std::unique_ptr<IDrawable>;
	using ImageUP = std::unique_ptr<Image>;

public:
	GifCreator(std::uint32_t width, std::uint32_t height, std::size_t nbFrames,
		std::uint32_t delay = defaultDelay);
	void registerObject(const std::string& uniqueName, IDrawableUP&&);

	template <typename T, typename ... Args>
	void changeObjectAt(std::size_t frameNb, const std::string& name, void (T::*)(const Args&...), const Args&... args);


	template <typename T, typename ... Args>
	void changeObjectFrom(std::size_t frameNb, const std::string& name, void (T::*)(const Args&...), const Args&... args);

	template <typename T, typename ... Args>
	void changeObjectTill(std::size_t frameNb, const std::string& name, void (T::*)(const Args&...), const Args&... args);

	template <typename T, typename ... Args>
	void changeObjectFromTill(std::size_t from, std::size_t till, const std::string& name, void (T::*)(const Args&...), const Args&... args);

	void createGif(const std::string& fileName = defaultFileName);

private:
	template <typename T, typename ... Args>
	void changeObject(const std::string& name, void (T::*)(const Args&...), const Args&... args);

private:
	void makeFrame(GifWriterHandle&);

private:
	GifCreator() = delete;

private:
	void updateImage();

private:
	ImageUP image_;
	std::uint32_t width_;
	std::uint32_t height_;
	std::uint32_t delay_;
	std::size_t nbFrames_;
	std::unordered_map<std::string, IDrawableUP> storage_;
	std::unordered_map<std::size_t, std::vector<std::function<void()>>> changes_;
	ColorMap pixelMapper_;
};

template <typename T, typename ... Args>
void GifCreator::changeObjectAt(std::size_t frameNb, const std::string& name, void (T::*f)(const Args&...), const Args&... args)
{
	changeObjectFromTill(frameNb, frameNb + 1, name, f, args...);
}

template <typename T, typename ... Args>
void GifCreator::changeObjectFrom(std::size_t frameNb, const std::string& name, void (T::*f)(const Args&...), const Args&... args)
{
	changeObjectFromTill(frameNb, nbFrames_, name, f, args...);
}

template <typename T, typename ... Args>
void GifCreator::changeObjectTill(std::size_t frameNb, const std::string& name, void (T::*f)(const Args&...), const Args&... args)
{
	changeObjectFromTill(0, frameNb, name, f, args...);
}

template <typename T, typename ... Args>
void GifCreator::changeObjectFromTill(std::size_t from, std::size_t till, const std::string& name, void (T::*f)(const Args&...), const Args&... args)
{
	for (std::size_t i = from; i < till; ++i)
		changes_[i].push_back([this, name, f, args...]{ changeObject(name, f, args...); });
}

template <typename T, typename ... Args>
void GifCreator::changeObject(const std::string& name, void (T::*f)(const Args&...), const Args&... args)
{
	if (!f) throw std::invalid_argument("Invalid functor");
	const auto o = dynamic_cast<T*>(storage_.at(name).get());
	if (!o) throw std::logic_error("Cannot convert object with the name " + name + " to " + typeid(T).name());
	(o->*f)(args...);
}
