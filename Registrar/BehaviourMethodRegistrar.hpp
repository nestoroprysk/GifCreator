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
	using lambda = std::function<void(Type::BehaviourUP& b,
		std::size_t from, std::size_t till, const QJsonValue& j)>;
	std::unordered_map<std::string, lambda> m_;
};

template <>
inline BehaviourMethodRegistrar<IMovable>::BehaviourMethodRegistrar()
{
	m_.insert({Value::IMovableMethod::moveUp,
		[](Type::BehaviourUP& b, std::size_t from, std::size_t till, const QJsonValue&){
			b->fromTill<IMovable, IMovable::moveUp>(from, till);
		}
	});
	m_.insert({Value::IMovableMethod::moveDown,
		[](Type::BehaviourUP& b, std::size_t from, std::size_t till, const QJsonValue&){
			b->fromTill<IMovable, IMovable::moveDown>(from, till);
		}
	});
	m_.insert({Value::IMovableMethod::moveLeft,
		[](Type::BehaviourUP& b, std::size_t from, std::size_t till, const QJsonValue&){
			b->fromTill<IMovable, IMovable::moveLeft>(from, till);
		} 
	});
	m_.insert({Value::IMovableMethod::moveRight,
		[](Type::BehaviourUP& b, std::size_t from, std::size_t till, const QJsonValue&){
			b->fromTill<IMovable, IMovable::moveRight>(from, till);
		}
	});
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
