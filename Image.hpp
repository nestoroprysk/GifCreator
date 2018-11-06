#pragma once
#include <memory>

struct Color;

class Image
{
public:
	Image(std::uint32_t width, std::uint32_t height);
	void fillNextPixel(Color const&);
	uint8_t const* get() const;
	void flush();

public:
	bool isComplete() const;

private:
	Image() = delete;

private:
	static const std::uint8_t rgba_ = 4;
	std::unique_ptr<std::uint8_t[]> data_;
	std::uint32_t width_;
	std::uint32_t height_;
	std::uint32_t pixelsFilled_;
};
