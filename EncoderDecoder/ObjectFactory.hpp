#pragma once

#include <Core/Type.hpp>
#include <Core/INameable.hpp>

#include "IObjectFactory.hpp"

template <typename T>
class ObjectFactory final : public IObjectFactory
{
public:
	auto create(const std::string&) -> Type::INameableUP override;
};

template <typename T>
auto ObjectFactory<T>::create(const std::string& name) -> Type::INameableUP
{
	auto result = std::make_unique<T>(name);
	return result;
}
