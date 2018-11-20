#pragma once

#include <string>
#include <Core/Type.hpp>

class QJsonValue;

class IBehaviourMapperFactory
{
public:
	virtual void map(const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue&, Type::BehaviourUP&) const = 0;
	virtual ~IBehaviourMapperFactory(){}
};
