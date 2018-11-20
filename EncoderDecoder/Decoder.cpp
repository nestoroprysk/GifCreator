#include <ios>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>

#include <Core/INameable.hpp>
#include <Core/Behaviour.hpp>

#include "Keys.hpp"
#include "ObjectMapper.hpp"
#include "BehaviourDecoder.hpp"
#include "Decoder.hpp"

Decoder::Decoder(const std::string& fileName)
	: fileName_(fileName)
	, content_(readFile())
	{}

auto Decoder::decodeGifParameters() const -> GifParameters
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

auto Decoder::decodeObjects() const -> std::vector<Type::INameableUP>
{
	std::vector<Type::INameableUP> result;
	const auto objectList = content_[Key::General::objectList].toArray();
	ObjectMapper m;
	for (const auto& o : objectList)
		result.push_back(m.makeConcreteObject(o[Key::Object::type].toString().toStdString(),
			o[Key::Object::name].toString().toStdString()));
	return result;
}

auto Decoder::decodeBehaviours() const -> std::vector<Type::BehaviourUP>
{
	std::vector<Type::BehaviourUP> result;
	const auto bs = content_[Key::General::behaviourList].toArray();
	BehaviourDecoder bd;
	for (const auto& o : bs)
		result.push_back(bd.decode(o));
	return result;
}

auto Decoder::decodeApplications() const -> std::vector<ObjectBehaviour>
{
	return std::vector<ObjectBehaviour>();
}

QJsonObject Decoder::readFile() const
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
