#pragma once

#include "IBehaviourMapperFactory.hpp"
#include "BehaviourDecoder.hpp"

template <typename T>
class BehaviourMapperFactory final : public IBehaviourMapperFactory
{
public:
	void map(const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue&, Type::BehaviourUP&) const override;
};

template <>
void BehaviourMapperFactory<BehaviourDecoder::IPositionableMapper>::map(const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue&, Type::BehaviourUP&) const;

template <>
void BehaviourMapperFactory<BehaviourDecoder::IMovableMapper>::map(const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue&, Type::BehaviourUP&) const;

template <>
void BehaviourMapperFactory<BehaviourDecoder::IColorableMapper>::map(const std::string& methodName,
		std::size_t from, std::size_t till, const QJsonValue&, Type::BehaviourUP&) const;
