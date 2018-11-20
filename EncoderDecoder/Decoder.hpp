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
	struct GifParameters{
		std::size_t width = 0;
		std::size_t height = 0;
		std::size_t nbFrames = 0;
		std::size_t delay = 0;
	};

private:
	static constexpr auto testingProject = "../EncoderDecoder/Project.json";

public:
	Decoder(const std::string& = testingProject);
	auto decodeGifParameters() const -> GifParameters;
	auto decodeObjects() const -> std::vector<Type::INameableUP>;
	auto decodeBehaviours() const -> std::vector<Type::BehaviourUP>;
	auto decodeApplications() const -> std::vector<ObjectBehaviour>;

private:
	QJsonObject readFile() const;

private:
	const std::string fileName_;
	const QJsonObject content_;
};
