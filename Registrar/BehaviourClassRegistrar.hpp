#pragma once

#include "IBehaviourClassRegistrar.hpp"
#include "BehaviourRegistrar.hpp"
#include "BehaviourMethodRegistrar.hpp"

class IPositionable;
class IMovable;
class IColorable;

template <typename T>
class BehaviourClassRegistrar final : public IBehaviourClassRegistrar
{
public:
	void registerClass(Type::BehaviourUP&, const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue&) const override;

private:
	BehaviourMethodRegistrar<T> bmr_;
};

template <>
void BehaviourClassRegistrar<IPositionable>::registerClass(Type::BehaviourUP&, const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue&) const;

template <>
void BehaviourClassRegistrar<IMovable>::registerClass(Type::BehaviourUP&, const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue&) const;

template <>
void BehaviourClassRegistrar<IColorable>::registerClass(Type::BehaviourUP&, const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue&) const;
