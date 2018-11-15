#pragma once
#include <vector>
#include <functional>
#include <optional>
#include "IDrawable.hpp"

class Behaviour
{
private:
	enum class Mode { Do, Undo };
	using SubChangesType = std::unordered_map<std::size_t, std::vector<std::function<void(IDrawable*, Mode)>>>;
	using ChangeSetType = std::unordered_map<std::size_t, std::vector<std::function<void(IDrawable*)>>>;

public:
	inline Behaviour(std::size_t nbFrames);

	inline auto getDo() const -> const ChangeSetType&;
	inline auto getUndo() const -> const ChangeSetType&;

	template <typename T, typename S, std::size_t nbCalls = 1, typename ... Args>
	void at(std::size_t, Args... args);

	template <typename T, typename S, std::size_t nbCalls = 1, typename ... Args>
	void from(std::size_t, Args... args);

	template <typename T, typename S, std::size_t nbCalls = 1, typename ... Args>
	void till(std::size_t, Args... args);

	template <typename T, typename S, std::size_t nbCalls = 1, typename ... Args>
	void fromTill(std::size_t from, std::size_t till, Args... args);

private:
	Behaviour() = delete;

private:
	template <typename T, typename S, std::size_t nbCalls, typename ... Args>
	void changeObject(IDrawable*, Mode, Args...);

private:
	mutable std::optional<ChangeSetType> doChanges_;
	mutable std::optional<ChangeSetType> undoChanges_;
	SubChangesType subChanges_;
	std::size_t nbFrames_;
};

inline Behaviour::Behaviour(std::size_t nbFrames) : nbFrames_(nbFrames) {};

inline auto Behaviour::getDo() const -> const ChangeSetType&
{
	if (!doChanges_){
		doChanges_.emplace();
		for (const auto& e : subChanges_)
			for (const auto& f : e.second)
				(*doChanges_)[e.first].push_back([f](IDrawable* o)
					{ f(o, Mode::Do); });
	}
	return doChanges_.value();
}

inline auto Behaviour::getUndo() const -> const ChangeSetType&
{
	if (!undoChanges_){
		undoChanges_.emplace();
		for (const auto& e : subChanges_)
			for (const auto& f : e.second)
				(*undoChanges_)[nbFrames_ - e.first].push_back([f](IDrawable* o)
					{ f(o, Mode::Undo); });
	}
	return undoChanges_.value();
}

template <typename T, typename S, std::size_t nbCalls, typename ... Args>
void Behaviour::at(std::size_t at, Args... args)
{
	fromTill<T, S, nbCalls>(at, at + 1, args...);
}

template <typename T, typename S, std::size_t nbCalls, typename ... Args>
void Behaviour::from(std::size_t from, Args... args)
{
	fromTill<T, S, nbCalls>(from, nbFrames_, args...);
}

template <typename T, typename S, std::size_t nbCalls, typename ... Args>
void Behaviour::till(std::size_t till, Args... args)
{
	fromTill<T, S, nbCalls>(0, till, args...);
}

template <typename T, typename S, std::size_t nbCalls, typename ... Args>
void Behaviour::fromTill(std::size_t from, std::size_t till, Args... args)
{
	for (std::size_t i = from; i < till; ++i)
		subChanges_[i].push_back([this, args...](IDrawable* o, Mode m)
			{ changeObject<T, S, nbCalls>(o, m, args...); });
}

template <typename T, typename S, std::size_t nbCalls, typename ... Args>
void Behaviour::changeObject(IDrawable* o, Mode m, Args... args)
{
	auto* c = dynamic_cast<T*>(o);
	if (m == Mode::Do)
		for (std::size_t i = 0; i < nbCalls; ++i)
			(c->*S().get())(args...);
	else
		for (std::size_t i = 0; i < nbCalls; ++i)
			(c->*S().mirror().get())(args...);
}
