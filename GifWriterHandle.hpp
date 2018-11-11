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
	std::string fileName_;
	std::uint32_t width_;
	std::uint32_t height_;
	std::uint32_t delay_;
	std::size_t nbFrames_;
};
