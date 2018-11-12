#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <functional>
#include "Utils.hpp"

class Image;
class GifWriterHandle;
class IDrawable;
class Behaviour;
class Color;

class GifCreator
{
private:
	static constexpr std::uint32_t defaultDelay_ = 10;
	static constexpr auto defaultFileName_ = "new.gif";

private:
	using IDrawableUP = std::unique_ptr<IDrawable>;
	using ImageUP = std::unique_ptr<Image>;

public:
	GifCreator(std::uint32_t width, std::uint32_t height, std::size_t nbFrames,
		std::uint32_t delay = defaultDelay_);
	void registerObject(const std::string& uniqueName, IDrawableUP&&);
	void setBehaviour(const std::string& objectName, const Behaviour&);
	void createGif(const std::string& fileName = defaultFileName_);
	~GifCreator();

private:
	void makeFrame(GifWriterHandle&);

private:
	GifCreator() = delete;

private:
	void updateImage();

private:
	ImageUP image_;
	const std::uint32_t width_;
	const std::uint32_t height_;
	const std::uint32_t delay_;
	const std::size_t nbFrames_;
	std::unordered_map<std::string, IDrawableUP> storage_;
	std::unordered_map<std::size_t, std::vector<std::function<void()>>> changes_;
	Utils::ColorMatrix pixelMapper_;
};
