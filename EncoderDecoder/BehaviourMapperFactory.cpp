#include "BehaviourMapperFactory.hpp"

template <>
void BehaviourMapperFactory<BehaviourDecoder::IPositionableMapper>::map(const std::string&,
		std::size_t, std::size_t, const QJsonValue&, Type::BehaviourUP&) const
{

}

template <>
void BehaviourMapperFactory<BehaviourDecoder::IMovableMapper>::map(const std::string&,
		std::size_t, std::size_t, const QJsonValue&, Type::BehaviourUP&) const
{

}

template <>
void BehaviourMapperFactory<BehaviourDecoder::IColorableMapper>::map(const std::string&,
		std::size_t, std::size_t, const QJsonValue&, Type::BehaviourUP&) const
{

}
