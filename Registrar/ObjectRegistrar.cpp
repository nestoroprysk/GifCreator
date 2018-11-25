#include <Core/ConcreteObjects/Square.hpp>

#include "ObjectRegistrar.hpp"
#include "Values.hpp"
#include "IObjectFactory.hpp"
#include "ObjectFactory.hpp"

namespace
{
	using SquareObjectFactory = ObjectFactory<Square>;
}

ObjectRegistrar::ObjectRegistrar()
{
	o_.insert({Value::ObjectType::Square, std::make_unique<SquareObjectFactory>()});
}

auto ObjectRegistrar::makeConcreteObject(const std::string& typeName, const std::string& objectName) -> Type::INameableUP
{
	return o_.at(typeName)->create(objectName);
}

ObjectRegistrar::~ObjectRegistrar(){}
