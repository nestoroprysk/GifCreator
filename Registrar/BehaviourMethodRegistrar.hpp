#pragma once

#include <functional>
#include <unordered_map>
#include <QJsonValue>

#include <Core/IPositionable.hpp>
#include <Core/IMovable.hpp>
#include <Core/IColorable.hpp>
#include "Values.hpp"

template <typename T>
class BehaviourMethodRegistrar
{
public:
	BehaviourMethodRegistrar();
	void operator()(Type::BehaviourUP&, const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue&) const;

private:
	using registerMethod = std::function<void(Type::BehaviourUP& b,
		std::size_t from, std::size_t till, const QJsonValue& j)>;
	std::unordered_map<std::string, registerMethod> m_;
};

template <>
inline void BehaviourMethodRegistrar<IPositionable>::operator()(Type::BehaviourUP& b, const std::string&,
		std::size_t from, std::size_t till, const QJsonValue&) const
{
	b->fromTill<IPositionable, IPositionable::gotoCenter>(from, till);
}

namespace
{
	template <typename T>
	void registerMovableMethod(Type::BehaviourUP& b, std::size_t from, std::size_t till, const QJsonValue&)
		{ b->fromTill<IMovable, T>(from, till); }
}

template <>
inline BehaviourMethodRegistrar<IMovable>::BehaviourMethodRegistrar()
{
	m_.insert({Value::IMovableMethod::moveUp, registerMovableMethod<IMovable::moveUp>});
	m_.insert({Value::IMovableMethod::moveDown, registerMovableMethod<IMovable::moveDown>});
	m_.insert({Value::IMovableMethod::moveLeft, registerMovableMethod<IMovable::moveLeft>});
	m_.insert({Value::IMovableMethod::moveRight, registerMovableMethod<IMovable::moveRight>});
}

template <>
inline void BehaviourMethodRegistrar<IMovable>::operator()(Type::BehaviourUP& b, const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue& j) const
{
	m_.at(methodName)(b, from, till, j);
}

template <>
inline void BehaviourMethodRegistrar<IColorable>::operator()(Type::BehaviourUP& b, const std::string&,
		std::size_t from, std::size_t till, const QJsonValue& j) const
{
	const auto colorJ = j[Value::IColorableMethod::SetColor::Argument::Color];
	const uint8_t cr = colorJ[Value::IColorableMethod::SetColor::Argument::ColorComponent::r].toInt();
	const uint8_t cg = colorJ[Value::IColorableMethod::SetColor::Argument::ColorComponent::g].toInt();
	const uint8_t cb = colorJ[Value::IColorableMethod::SetColor::Argument::ColorComponent::b].toInt();
	b->fromTill<IColorable, IColorable::setColor>(from, till, Color{cr, cg, cb});
}

template <typename T>
inline void BehaviourMethodRegistrar<T>::operator()(Type::BehaviourUP&, const std::string&,
		std::size_t, std::size_t, const QJsonValue&) const
{

}

template <typename T>
inline BehaviourMethodRegistrar<T>::BehaviourMethodRegistrar()
{

}
