#pragma once

#include <functional>
#include <unordered_map>
#include <QJsonValue>

#include <Core/IPositionable.hpp>
#include <Core/IMovable.hpp>
#include <Core/IZoomable.hpp>
#include <Core/IColorable.hpp>
#include "Values.hpp"
#include "IBehaviourClassRegistrar.hpp"

template <typename T>
class BehaviourMethodRegistrar
{
public:
	BehaviourMethodRegistrar();
	auto operator()(const std::string& methodName, std::size_t from,
		std::size_t till, const QJsonValue&) const;

private:
	using MethodRegistrar = std::function<IBehaviourClassRegistrar::BehaviourComponentRegistrar(
		std::size_t from, std::size_t till, const QJsonValue&)>;
	std::unordered_map<std::string, MethodRegistrar> m_;
};

namespace
{
	template <typename C, typename M>
	auto registerMonad(std::size_t from, std::size_t till, const QJsonValue&)
	{
		return [from, till](Type::BehaviourUP& b){ b->fromTill<C, M>(from, till); };
	}
}

// IPositionable instantiation

template <>
inline auto BehaviourMethodRegistrar<IPositionable>::operator()(const std::string&,
		std::size_t from, std::size_t till, const QJsonValue& j) const
{
	return registerMonad<IPositionable, IPositionable::gotoCenter>(from, till, j);
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
inline auto BehaviourMethodRegistrar<IMovable>::operator()(const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue& j) const
{
	return m_.at(methodName)(from, till, j);
}

// IZoomable instantiation

template <>
inline BehaviourMethodRegistrar<IZoomable>::BehaviourMethodRegistrar()
{
	m_.insert({Value::IZoomableMethod::zoomIn, registerMonad<IZoomable, IZoomable::zoomIn>});
	m_.insert({Value::IZoomableMethod::zoomOut, registerMonad<IZoomable, IZoomable::zoomOut>});
}

template <>
inline auto BehaviourMethodRegistrar<IZoomable>::operator()(const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue& j) const
{
	return m_.at(methodName)(from, till, j);
}

// IColorable instantiation

template <>
inline auto BehaviourMethodRegistrar<IColorable>::operator()(const std::string&,
		std::size_t from, std::size_t till, const QJsonValue& j) const
{
	const auto colorJ = j[Value::IColorableMethod::SetColor::Argument::Color];
	const uint8_t cr = colorJ[Value::IColorableMethod::SetColor::Argument::ColorComponent::r].toInt();
	const uint8_t cg = colorJ[Value::IColorableMethod::SetColor::Argument::ColorComponent::g].toInt();
	const uint8_t cb = colorJ[Value::IColorableMethod::SetColor::Argument::ColorComponent::b].toInt();
	return [from, till, cr, cg, cb](Type::BehaviourUP& b)
		{ b->fromTill<IColorable, IColorable::setColor>(from, till, Color{cr, cg, cb}); };
}

// Default constructor

template <typename T>
inline BehaviourMethodRegistrar<T>::BehaviourMethodRegistrar()
{

}
