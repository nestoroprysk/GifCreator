#pragma once

namespace Value
{
	namespace ObjectType
	{
		static constexpr auto Square = "Square";
		static constexpr auto Circle = "Circle";
		static constexpr auto Triangle = "Triangle";
	}
	namespace BehaviourClassType
	{
		static constexpr auto IPositionable = "IPositionable";
		static constexpr auto IMovable = "IMovable";
		static constexpr auto IColorable = "IColorable";
	}
	namespace IMovableMethod
	{
		static constexpr auto moveUp = "moveUp";
		static constexpr auto moveDown = "moveDown";
		static constexpr auto moveLeft = "moveLeft";
		static constexpr auto moveRight = "moveRight";
	}
}
