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
	IBehaviourClassRegistrar::BehaviourComponentRegistrar
		operator()(const std::string& methodName,
			std::size_t from, std::size_t till, const QJsonValue&) const override;

private:
	BehaviourMethodRegistrar<T> bmr_;
};

template <typename T>
auto BehaviourClassRegistrar<T>::operator()(const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue& j) const
			-> IBehaviourClassRegistrar::BehaviourComponentRegistrar
{
	return bmr_(methodName, from, till, j);
}
