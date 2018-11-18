#pragma once

#include <string>
#include <Core/Type.hpp>
#include <QJsonObject>

class Behaviour;

class Decoder
{
public:
	using ObjectBehaviour = std::pair<std::string, std::string>;

public:
	Decoder(const std::string& = "../EncoderDecoder/Project.json");
	auto decodeObjects() const -> std::vector<Type::INameableUP>;
	auto decodeBehaviours() const -> std::vector<Behaviour>;
	auto decodeApplications() const -> std::vector<ObjectBehaviour>;

private:
	QJsonObject readFile() const;

private:
	const std::string fileName_;
	const QJsonObject content_;
};
