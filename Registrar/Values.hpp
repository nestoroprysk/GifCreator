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
		static constexpr auto IZoomable = "IZoomable";
		static constexpr auto IColorable = "IColorable";
	}
	namespace IPositionableMethod
	{
		static constexpr auto gotoCenter = "gotoCenter";
	}
	namespace IMovableMethod
	{
		static constexpr auto moveUp = "moveUp";
		static constexpr auto moveDown = "moveDown";
		static constexpr auto moveLeft = "moveLeft";
		static constexpr auto moveRight = "moveRight";
	}
	namespace IZoomableMethod
	{
		static constexpr auto zoomIn = "zoomIn";
		static constexpr auto zoomOut = "zoomOut";
	}
	namespace IColorableMethod
	{
		static constexpr auto setColor = "setColor";
		namespace SetColor
		{
			namespace Argument
			{
				static constexpr auto Color = "Color";
				namespace ColorComponent
				{
					static constexpr auto r = "r";
					static constexpr auto g = "g";
					static constexpr auto b = "b";
				}
			}
		}
	}
	namespace Application
	{
		namespace Mode
		{
			static constexpr auto doMode = "Do";
			static constexpr auto undoMode = "Undo";
		}
	}
}
