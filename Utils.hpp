#pragma once
#include <vector>

#define lambda(x) ([&]{(x);})

class Color;

namespace Utils
{
	using ColorMatrix = std::vector<std::vector<Color>>;
}
