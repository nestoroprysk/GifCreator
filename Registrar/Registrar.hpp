#pragma once

#include <string>
#include <Core/Type.hpp>
#include <QJsonObject>

class Behaviour;

class Registrar
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
	static constexpr auto testingProject = "../Registrar/Project.json";

public:
	Registrar(const std::string& = testingProject);
	auto registerGifParameters() const -> GifParameters;
	auto registerObjects() const -> std::vector<Type::INameableUP>;
	auto registerBehaviours() const -> std::vector<Type::BehaviourUP>;
	auto registerApplications() const -> std::vector<ObjectBehaviour>;

private:
	QJsonObject readFile() const;

private:
	const std::string fileName_;
	const QJsonObject content_;
};
