#pragma once

#include <string>
#include <unordered_map>

#include <Core/Type.hpp>

class IObjectFactory;

class ObjectMapper
{
public:
	auto makeConcreteObject(const std::string& typeName, const std::string& objectName) -> Type::INameableUP;

public:
	ObjectMapper();
	~ObjectMapper();

public:
	using IObjectFactoryUP = std::unique_ptr<IObjectFactory>;

private:
	std::unordered_map<std::string, IObjectFactoryUP> o_;
};
