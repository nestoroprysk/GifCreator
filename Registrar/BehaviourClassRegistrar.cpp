#include <Core/Behaviour.hpp>
#include <Core/IPositionable.hpp>
#include <Core/IMovable.hpp>
#include <Core/IColorable.hpp>

#include "BehaviourClassRegistrar.hpp"

template <>
void BehaviourClassRegistrar<IPositionable>::registerClass(Type::BehaviourUP&, const std::string&,
		std::size_t, std::size_t, const QJsonValue&) const
{

}

template <>
void BehaviourClassRegistrar<IMovable>::registerClass(Type::BehaviourUP& b, const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue& j) const
{
	bmr_(b, methodName, from, till, j);
}

template <>
void BehaviourClassRegistrar<IColorable>::registerClass(Type::BehaviourUP&, const std::string&,
		std::size_t, std::size_t, const QJsonValue&) const
{

}
