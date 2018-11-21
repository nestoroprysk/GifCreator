#include <Core/ConcreteObjects/Square.hpp>
#include <Core/ConcreteObjects/Circle.hpp>
#include <Core/ConcreteObjects/Triangle.hpp>

#include "ObjectRegistrar.hpp"
#include "Values.hpp"
#include "IObjectFactory.hpp"
#include "ObjectFactory.hpp"

namespace
{
	using SquareObjectFactory = ObjectFactory<Square>;
	using CircleObjectFactory = ObjectFactory<Circle>;
	using TriangleObjectFactory = ObjectFactory<Triangle>;
}

ObjectRegistrar::ObjectRegistrar()
{
	o_.insert({Value::ObjectType::Square, std::make_unique<SquareObjectFactory>()});
	o_.insert({Value::ObjectType::Circle, std::make_unique<CircleObjectFactory>()});
	o_.insert({Value::ObjectType::Triangle, std::make_unique<TriangleObjectFactory>()});
}

auto ObjectRegistrar::makeConcreteObject(const std::string& typeName, const std::string& objectName) -> Type::INameableUP
{
	return o_.at(typeName)->create(objectName);
}

ObjectRegistrar::~ObjectRegistrar(){}
