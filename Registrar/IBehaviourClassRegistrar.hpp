#pragma once

#include <string>
#include <Core/Type.hpp>

class QJsonValue;

class IBehaviourClassRegistrar
{
public:
	virtual void registerClass(Type::BehaviourUP&, const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue&) const = 0;
	virtual ~IBehaviourClassRegistrar(){}
};
