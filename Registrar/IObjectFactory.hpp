#pragma once

class string;

class IObjectFactory
{
public:
	virtual auto create(const std::string&) -> Type::INameableUP = 0;
	virtual ~IObjectFactory(){}
};
