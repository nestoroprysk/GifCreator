#include <ThirdParties/gif.h>

#include "GifWriterHandle.hpp"

GifWriterHandle::GifWriterHandle(const std::string& fileName, std::uint32_t width, std::uint32_t height, std::uint32_t delay)
	: gwUP_(std::make_unique<GifWriter>())
	, fileName_(fileName)
	, width_(width)
	, height_(height)
	, delay_(delay)
{
	GifBegin(gwUP_.get(), fileName.c_str(), width, height, delay_);
}

void GifWriterHandle::writeFrame(const uint8_t* image)
{
	GifWriteFrame(gwUP_.get(), image, width_, height_, delay_);
}

GifWriterHandle::~GifWriterHandle()
{
	GifEnd(gwUP_.get());
}
