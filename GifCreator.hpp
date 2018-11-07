#pragma once
#include <memory>
#include <vector>
#include "Color.hpp"

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
	void registerObject(IDrawableUP);
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
	std::vector<IDrawableUP> storage_;
	ColorMap map_;
};
