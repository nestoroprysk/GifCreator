#pragma once

namespace Key
{
	namespace General
	{
		static constexpr auto objectList = "Objects";
		static constexpr auto behaviourList = "Behaviours";
		static constexpr auto applicationList = "Applications";
	}
	namespace Object
	{
		static constexpr auto name = "Name";
		static constexpr auto type = "Type";
	}
	namespace Behaviour
	{
		static constexpr auto name = "Name";
		static constexpr auto componentList = "Components";
		namespace Component
		{
			static constexpr auto className = "Class";
			static constexpr auto methodName = "Method";
			static constexpr auto rangeAt = "At";
		}
	}
	namespace Application
	{
		static constexpr auto objectName = "ObjectName";
		static constexpr auto behaviourName = "BehaviourName";
	}
}
