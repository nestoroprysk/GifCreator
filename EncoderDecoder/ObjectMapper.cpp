#include <Core/ConcreteObjects/Square.hpp>
#include <Core/ConcreteObjects/Circle.hpp>

#include "ObjectMapper.hpp"
#include "Values.hpp"
#include "IObjectFactory.hpp"
#include "ObjectFactory.hpp"

namespace
{
	using SquareObjectFactory = ObjectFactory<Square>;
	using CircleObjectFactory = ObjectFactory<Circle>;
}

ObjectMapper::ObjectMapper()
{
	o_.insert({Value::ObjectType::Square, std::make_unique<SquareObjectFactory>()});
	o_.insert({Value::ObjectType::Circle, std::make_unique<CircleObjectFactory>()});
}

auto ObjectMapper::makeConcreteObject(const std::string& typeName, const std::string& objectName) -> Type::INameableUP
{
	return o_.at(typeName)->create(objectName);
}

ObjectMapper::~ObjectMapper(){}
