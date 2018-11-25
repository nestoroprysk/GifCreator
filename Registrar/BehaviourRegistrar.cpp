#include <Core/Behaviour.hpp>
#include <QJsonArray>
#include <Core/IPositionable.hpp>
#include <Core/IMovable.hpp>
#include <Core/IColorable.hpp>

#include "Keys.hpp"
#include "Values.hpp"
#include "BehaviourRegistrar.hpp"
#include "BehaviourClassRegistrar.hpp"

auto BehaviourRegistrar::makeBehaviour(const QJsonValue& o) -> Type::BehaviourUP
{
	const auto name = o[Key::Behaviour::name].toString();
	const auto nbFrames = o[Key::Behaviour::nbFrames].toInt();
	result_ = std::make_unique<Behaviour>(name.toStdString(), nbFrames);
	const auto componentList = o[Key::Behaviour::componentList].toArray();
	for (const auto& c : componentList)
		makeComponent(c);
	return std::move(result_);
}

namespace
{
	using IPositionableRegistrar = BehaviourClassRegistrar<IPositionable>;
	using IMovableRegistrar = BehaviourClassRegistrar<IMovable>;
	using IZoomableRegistrar = BehaviourClassRegistrar<IZoomable>;
	using IColorableRegistrar = BehaviourClassRegistrar<IColorable>;
}

BehaviourRegistrar::BehaviourRegistrar()
{
	m_.insert({Value::BehaviourClassType::IPositionable, std::make_unique<IPositionableRegistrar>()});
	m_.insert({Value::BehaviourClassType::IMovable, std::make_unique<IMovableRegistrar>()});
	m_.insert({Value::BehaviourClassType::IZoomable, std::make_unique<IZoomableRegistrar>()});
	m_.insert({Value::BehaviourClassType::IColorable, std::make_unique<IColorableRegistrar>()});
}

BehaviourRegistrar::~BehaviourRegistrar(){}

void BehaviourRegistrar::makeComponent(const QJsonValue& o)
{
	const auto className = o[Key::Behaviour::Component::className].toString();
	const auto methodName = o[Key::Behaviour::Component::methodName].toString();
	const auto from = o[Key::Behaviour::Component::from].toInt();
	const auto till = o[Key::Behaviour::Component::till].toInt();
	m_[className.toStdString()]->registerClass(result_, methodName.toStdString(), from, till, o);
}
