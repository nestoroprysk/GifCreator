#pragma once

#include <vector>
#include <memory>
#include <functional>

struct Color;
class IDrawable;
class INameable;
class Behaviour;

namespace Type
{
	using ColorMatrix = std::vector<std::vector<Color>>;
	using IDrawableUP = std::unique_ptr<IDrawable>;
	using INameableUP = std::unique_ptr<INameable>;
	using BehaviourUP = std::unique_ptr<Behaviour>;
}
