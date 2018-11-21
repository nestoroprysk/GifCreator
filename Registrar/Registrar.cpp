#include <ios>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>

#include <Core/INameable.hpp>
#include <Core/Behaviour.hpp>

#include "Keys.hpp"
#include "ObjectRegistrar.hpp"
#include "BehaviourRegistrar.hpp"
#include "Registrar.hpp"

Registrar::Registrar(const std::string& fileName)
	: fileName_(fileName)
	, content_(readFile())
	{}

auto Registrar::registerGifParameters() const -> GifParameters
{
	GifParameters result;
	const auto value = content_.value(QString(Key::General::gifParameters));
	const auto object = value.toObject();
	result.width = object[Key::GifParameters::width].toInt();
	result.height = object[Key::GifParameters::height].toInt();
	result.nbFrames = object[Key::GifParameters::nbFrames].toInt();
	result.delay = object[Key::GifParameters::delay].toInt();
	return result;
}

auto Registrar::registerObjects() const -> std::vector<Type::INameableUP>
{
	std::vector<Type::INameableUP> result;
	const auto objectList = content_[Key::General::objectList].toArray();
	ObjectRegistrar m;
	for (const auto& o : objectList)
		result.push_back(m.makeConcreteObject(o[Key::Object::type].toString().toStdString(),
			o[Key::Object::name].toString().toStdString()));
	return result;
}

auto Registrar::registerBehaviours() const -> std::vector<Type::BehaviourUP>
{
	std::vector<Type::BehaviourUP> result;
	const auto bs = content_[Key::General::behaviourList].toArray();
	BehaviourRegistrar bd;
	for (const auto& o : bs)
		result.push_back(bd.makeBehaviour(o));
	return result;
}

auto Registrar::registerApplications() const -> std::vector<ObjectBehaviour>
{
	return {};
}

QJsonObject Registrar::readFile() const
{
	QFile file(QString::fromStdString(fileName_));
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	const QString stringContent = file.readAll();
	file.close();
	if (stringContent.isEmpty())
		throw std::ios_base::failure("Failed to open the project.");
	const auto documentContent = QJsonDocument::fromJson(stringContent.toUtf8());
	const auto result = documentContent.object();
	return result;
}
