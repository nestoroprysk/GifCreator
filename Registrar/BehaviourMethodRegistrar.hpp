#pragma once

#include <functional>
#include <unordered_map>
#include <QJsonValue>

#include <Core/IPositionable.hpp>
#include <Core/IMovable.hpp>
#include <Core/IZoomable.hpp>
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

namespace
{
	template <typename C, typename M>
	void registerMonad(Type::BehaviourUP& b, std::size_t from, std::size_t till, const QJsonValue&)
		{ b->fromTill<C, M>(from, till); }
}

// IPositionable instantiation

template <>
inline void BehaviourMethodRegistrar<IPositionable>::operator()(Type::BehaviourUP& b, const std::string&,
		std::size_t from, std::size_t till, const QJsonValue&) const
{
	b->fromTill<IPositionable, IPositionable::gotoCenter>(from, till);
}

// IMovable instantiation

template <>
inline BehaviourMethodRegistrar<IMovable>::BehaviourMethodRegistrar()
{
	m_.insert({Value::IMovableMethod::moveUp, registerMonad<IMovable, IMovable::moveUp>});
	m_.insert({Value::IMovableMethod::moveDown, registerMonad<IMovable, IMovable::moveDown>});
	m_.insert({Value::IMovableMethod::moveLeft, registerMonad<IMovable, IMovable::moveLeft>});
	m_.insert({Value::IMovableMethod::moveRight, registerMonad<IMovable, IMovable::moveRight>});
}

template <>
inline void BehaviourMethodRegistrar<IMovable>::operator()(Type::BehaviourUP& b, const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue& j) const
{
	m_.at(methodName)(b, from, till, j);
}

// IZoomable instantiation

template <>
inline BehaviourMethodRegistrar<IZoomable>::BehaviourMethodRegistrar()
{
	m_.insert({Value::IZoomableMethod::zoomIn, registerMonad<IZoomable, IZoomable::zoomIn>});
	m_.insert({Value::IZoomableMethod::zoomOut, registerMonad<IZoomable, IZoomable::zoomOut>});
}

template <>
inline void BehaviourMethodRegistrar<IZoomable>::operator()(Type::BehaviourUP& b, const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue& j) const
{
	m_.at(methodName)(b, from, till, j);
}

// IColorable instantiation

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

// Default constructor

template <typename T>
inline BehaviourMethodRegistrar<T>::BehaviourMethodRegistrar()
{

}
