#pragma once

#include <functional>
#include <unordered_map>
#include <QJsonValue>

#include <Core/IMovable.hpp>
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

template <typename T>
inline BehaviourMethodRegistrar<T>::BehaviourMethodRegistrar()
{

}

template <typename T>
inline void BehaviourMethodRegistrar<T>::operator()(Type::BehaviourUP&, const std::string&,
		std::size_t, std::size_t, const QJsonValue&) const
{

}
