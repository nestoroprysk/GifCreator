#pragma once
#include <vector>
#include <memory>
#include <functional>

class Color;
class IDrawable;

namespace Type
{
	using ColorMatrix = std::vector<std::vector<Color>>;
	using IDrawableUP = std::unique_ptr<IDrawable>;
}
