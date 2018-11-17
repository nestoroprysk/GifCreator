#pragma once
#include <memory>

struct Color;

class Image
{
public:
	Image(std::uint32_t width, std::uint32_t height);
	void fillNextPixel(const Color&);
	uint8_t const* get() const;
	void flush();

public:
	bool isComplete() const;

private:
	Image() = delete;

private:
	std::unique_ptr<std::uint8_t[]> data_;
	std::uint32_t pixelsFilled_;
	const std::uint32_t width_;
	const std::uint32_t height_;

private:
	static constexpr std::uint8_t rgba_ = 4;
};
