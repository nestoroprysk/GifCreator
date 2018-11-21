#pragma once

#include <any>
#include <tuple>
#include <unordered_map>
#include <iostream>
#include <QJsonValue>

#include <Core/IMovable.hpp>
#include "Values.hpp"

template <typename T>
class BehaviourMethodRegistrar
{
public:
	BehaviourMethodRegistrar();
	auto operator()(Type::BehaviourUP&, const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue&) const;

private:
	std::any tuple_;
	std::unordered_map<std::string, std::any> m_;
};

namespace
{
	enum class IMovableTupleIndex { moveUp, moveDown, moveLeft, moveRight };
}

template <>
inline BehaviourMethodRegistrar<IMovable>::BehaviourMethodRegistrar()
{
	tuple_ = std::make_tuple(IMovable::moveUp(), IMovable::moveDown(), IMovable::moveLeft(), IMovable::moveRight());
	m_.insert({Value::IMovableMethod::moveUp, IMovableTupleIndex::moveUp});
	m_.insert({Value::IMovableMethod::moveDown, IMovableTupleIndex::moveDown});
	m_.insert({Value::IMovableMethod::moveLeft, IMovableTupleIndex::moveLeft});
	m_.insert({Value::IMovableMethod::moveRight, IMovableTupleIndex::moveRight});
}

template <>
inline auto BehaviourMethodRegistrar<IMovable>::operator()(Type::BehaviourUP&, const std::string&,
		std::size_t, std::size_t, const QJsonValue&) const
{
	// In progress
}

template <typename T>
inline BehaviourMethodRegistrar<T>::BehaviourMethodRegistrar()
{

}

template <typename T>
inline auto BehaviourMethodRegistrar<T>::operator()(Type::BehaviourUP&, const std::string&,
		std::size_t, std::size_t, const QJsonValue&) const
{
	return -1;
}
