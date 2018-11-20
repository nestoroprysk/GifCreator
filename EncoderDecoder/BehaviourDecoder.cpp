#include <Core/Behaviour.hpp>
#include <QJsonArray>
#include <Core/IPositionable.hpp>

#include "Keys.hpp"
#include "Values.hpp"
#include "BehaviourDecoder.hpp"
#include "BehaviourMapperFactory.hpp"

auto BehaviourDecoder::decode(const QJsonValue& o) -> Type::BehaviourUP
{
	const auto name = o[Key::Behaviour::name].toString();
	const auto nbFrames = o[Key::Behaviour::nbFrames].toInt();
	result_ = std::make_unique<Behaviour>(name.toStdString(), nbFrames);
	const auto componentList = o[Key::Behaviour::componentList].toArray();
	for (const auto& c : componentList)
		decodeComponent(c);
	return std::move(result_);
}

namespace
{
	using IPositionableMapperFactory = BehaviourMapperFactory<BehaviourDecoder::IPositionableMapper>;
	using IMoveableMapperFactory = BehaviourMapperFactory<BehaviourDecoder::IMovableMapper>;
	using IColorableMapperFactory = BehaviourMapperFactory<BehaviourDecoder::IColorableMapper>;
}

BehaviourDecoder::BehaviourDecoder()
{
	m_.insert({Value::BehaviourClassType::IPositionable, std::make_unique<IPositionableMapperFactory>()});
	m_.insert({Value::BehaviourClassType::IMovable, std::make_unique<IMoveableMapperFactory>()});
	m_.insert({Value::BehaviourClassType::IColorable, std::make_unique<IColorableMapperFactory>()});
}

BehaviourDecoder::~BehaviourDecoder(){}

void BehaviourDecoder::decodeComponent(const QJsonValue& o)
{
	const auto className = o[Key::Behaviour::Component::className].toString();
	const auto methodName = o[Key::Behaviour::Component::methodName].toString();
	const auto from = o[Key::Behaviour::Component::from].toInt();
	const auto till = o[Key::Behaviour::Component::till].toInt();
	m_[className.toStdString()]->map(methodName.toStdString(), from, till, o, result_);
}

void BehaviourDecoder::IPositionableMapper::GotoCenter::operator()
		(Type::BehaviourUP& r, std::size_t from, std::size_t till) const{
	r->fromTill<IPositionable, IPositionable::gotoCenter>(from, till);
}