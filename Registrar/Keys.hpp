#pragma once

namespace Key
{
	namespace General
	{
		static constexpr auto gifParameters = "GifParameters";
		static constexpr auto objectList = "Objects";
		static constexpr auto behaviourList = "Behaviours";
		static constexpr auto applicationList = "Applications";
	}
	namespace GifParameters
	{
		static constexpr auto width = "Width";
		static constexpr auto height = "Height";
		static constexpr auto nbFrames = "NbFrames";
		static constexpr auto delay = "Delay";
	}
	namespace Object
	{
		static constexpr auto name = "Name";
		static constexpr auto type = "Type";
	}
	namespace Behaviour
	{
		static constexpr auto name = "Name";
		static constexpr auto nbFrames = "NbFrames";
		static constexpr auto componentList = "Components";
		namespace Component
		{
			static constexpr auto className = "Class";
			static constexpr auto methodName = "Method";
			static constexpr auto from = "From";
			static constexpr auto till = "Till";
		}
	}
	namespace Application
	{
		static constexpr auto objectName = "ObjectName";
		static constexpr auto behaviourName = "BehaviourName";
		static constexpr auto at = "At";
	}
}
