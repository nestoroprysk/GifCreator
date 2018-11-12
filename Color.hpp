#pragma once

struct Color
{
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t a = 0;
};

class BasicColors
{
private:
	BasicColors() = delete;
	static constexpr uint8_t min = 0;
	static constexpr uint8_t max = 255;

public:
	static constexpr Color black;
	static constexpr Color white{max, max, max};
	static constexpr Color red{max};
	static constexpr Color green{min, max};
	static constexpr Color blue{min, min, max};
};

struct Pixel
{
	std::size_t x = 0;
	std::size_t y = 0;
	Color c;
	bool operator==(Pixel const& rhs) const
		{ return x == rhs.x && y == rhs.y; }
};
