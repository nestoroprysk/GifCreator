#pragma once
#include <memory>

class Image;
struct GifWriter;

class GifCreator
{
private:
	static const std::uint32_t defaultDelay = 10;
	static constexpr auto defaultFileName = "new.gif";

public:
	GifCreator(std::uint32_t width, std::uint32_t height,
		std::uint32_t delay = defaultDelay, const char* fileName = defaultFileName);
	void drawBlackAndWhiteFrames();
	void drawMovingDot();
	~GifCreator();

private:
	GifCreator() = delete;

private:
	void makeFrame();

private:
	std::unique_ptr<Image> image_;
	std::unique_ptr<GifWriter> writer_;
	std::uint32_t width_;
	std::uint32_t height_;
	std::uint32_t delay_;
};
