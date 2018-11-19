#pragma once

#include <memory>
#include <string>

struct GifWriter;

class GifWriterHandle
{
public:
	GifWriterHandle(const std::string& fileName, std::uint32_t width, std::uint32_t height, std::uint32_t delay_);
	void writeFrame(const uint8_t* image);
	~GifWriterHandle();

private:
	std::unique_ptr<GifWriter> gwUP_;
	const std::string fileName_;
	const std::uint32_t width_ = 0;
	const std::uint32_t height_ = 0;
	const std::uint32_t delay_ = 0;
};
