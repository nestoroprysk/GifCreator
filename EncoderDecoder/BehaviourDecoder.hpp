#pragma once

#include <string>
#include <unordered_map>
#include <QJsonValue>

#include <Core/Type.hpp>
#include <Core/Behaviour.hpp>
#include <Core/IPositionable.hpp>

class IBehaviourMapperFactory;

class BehaviourDecoder
{
public:
	auto decode(const QJsonValue&) -> Type::BehaviourUP;

public:
	BehaviourDecoder();
	~BehaviourDecoder();

private:
	void decodeComponent(const QJsonValue&);

private:
	Type::BehaviourUP result_;

public:
	struct IPositionableMapper{
		struct GotoCenter{
			void operator()(Type::BehaviourUP& r, std::size_t from, std::size_t till) const;
		};
	};
	struct IMovableMapper{
		struct MoveUp{

		};
		struct MoveDown{

		};
		struct MoveLeft{

		};
		struct MoveRight{

		};
	};
	struct IColorableMapper{
		struct SetColor{

		};
	};

public:
	using IBehaviourMapperFactoryUP = std::unique_ptr<IBehaviourMapperFactory>;

private:
	std::unordered_map<std::string, IBehaviourMapperFactoryUP> m_;
};
