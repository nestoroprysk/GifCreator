#pragma once
#include <vector>
#include <functional>
#include "IDrawable.hpp"

class Behaviour
{
private:
	using ChangeSetType = std::unordered_map<std::size_t, std::vector<std::function<void(IDrawable*)>>>;

public:
	inline Behaviour(std::size_t nbFrames);

	inline auto get() const -> const ChangeSetType&;

	template <typename T, typename ... Params, typename ... Args>
	void at(std::size_t frameNb, void (T::*f)(Params...), Args... args);

	template <typename T, typename ... Params, typename ... Args>
	void from(std::size_t frameNb, void (T::*f)(Params...), Args... args);

	template <typename T, typename ... Params, typename ... Args>
	void till(std::size_t frameNb, void (T::*f)(Params...), Args... args);

	template <typename T, typename ... Params, typename ... Args>
	void fromTill(std::size_t from, std::size_t till, void (T::*f)(Params...), Args... args);

private:
	Behaviour() = delete;

private:
	template <typename T, typename ... Params, typename ... Args>
	void changeObject(T* o, void (T::*)(Params...), Args... args);

private:
	ChangeSetType changes_;
	std::size_t nbFrames_;
};

inline Behaviour::Behaviour(std::size_t nbFrames) : nbFrames_(nbFrames) {};

inline auto Behaviour::get() const -> const ChangeSetType&
{
	return changes_;
}

template <typename T, typename ... Params, typename ... Args>
void Behaviour::at(std::size_t frameNb, void (T::*f)(Params...), Args... args)
{
	fromTill(frameNb, frameNb + 1, f, args...);
}

template <typename T, typename ... Params, typename ... Args>
void Behaviour::from(std::size_t frameNb, void (T::*f)(Params...), Args... args)
{
	fromTill(frameNb, nbFrames_, f, args...);
}

template <typename T, typename ... Params, typename ... Args>
void Behaviour::till(std::size_t frameNb, void (T::*f)(Params...), Args... args)
{
	fromTill(0, frameNb, f, args...);
}

template <typename T, typename ... Params, typename ... Args>
void Behaviour::fromTill(std::size_t from, std::size_t till, void (T::*f)(Params...), Args... args)
{
	for (std::size_t i = from; i < till; ++i)
		changes_[i].push_back([this, f, args...](IDrawable* o){ changeObject(dynamic_cast<T*>(o), f, args...); });
}

template <typename T, typename ... Params, typename ... Args>
void Behaviour::changeObject(T* o, void (T::*f)(Params...), Args... args)
{
	if (!o) throw std::logic_error(std::string("Cannot convert object with the name to ") + typeid(T).name());
	if (!f) throw std::invalid_argument("Invalid functor");
	(o->*f)(args...);
}
