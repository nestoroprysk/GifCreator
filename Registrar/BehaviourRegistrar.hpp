#pragma once

#include <string>
#include <unordered_map>
#include <QJsonValue>

#include <Core/Type.hpp>

class IBehaviourClassRegistrar;

class BehaviourRegistrar
{
public:
	auto makeBehaviour(const QJsonValue&) -> Type::BehaviourUP;

public:
	BehaviourRegistrar();
	~BehaviourRegistrar();

private:
	void makeComponent(const QJsonValue&);

private:
	Type::BehaviourUP result_;

public:
	using IBehaviourClassRegistrarUP = std::unique_ptr<IBehaviourClassRegistrar>;

private:
	std::unordered_map<std::string, IBehaviourClassRegistrarUP> m_;
};
