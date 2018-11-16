#pragma once
#include <optional>
#include "IDrawable.hpp"
#include "Type.hpp"

class Behaviour
{
private:
	enum class Mode { Do, Undo };

public:
	using SubChangeType = std::unordered_map<std::size_t, std::vector<std::function<void(const Type::IDrawableUP&, Mode)>>>;
	using ChangeSetType = std::unordered_map<std::size_t, std::vector<std::function<void(const Type::IDrawableUP&)>>>;

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
	void changeObject(const Type::IDrawableUP&, Mode, Args...);

	template <typename T, typename F, typename ... Args>
	void changeObjectSpecifically(T& o, F, std::size_t nbCalls, Args...);

private:
	mutable std::optional<ChangeSetType> doChanges_;
	mutable std::optional<ChangeSetType> undoChanges_;
	SubChangeType subChanges_;
	std::size_t nbFrames_;
};

inline Behaviour::Behaviour(std::size_t nbFrames) : nbFrames_(nbFrames) {};

inline auto Behaviour::getDo() const -> const ChangeSetType&
{
	if (!doChanges_){
		doChanges_.emplace();
		for (const auto& e : subChanges_)
			for (const auto& f : e.second)
				(*doChanges_)[e.first].push_back([f](const Type::IDrawableUP& o)
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
				(*undoChanges_)[nbFrames_ - e.first].push_back([f](const Type::IDrawableUP& o)
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
		subChanges_[i].push_back([this, args...](const Type::IDrawableUP& o, Mode m)
			{ changeObject<T, S, nbCalls>(o, m, args...); });
}

template <typename T, typename S, std::size_t nbCalls, typename ... Args>
void Behaviour::changeObject(const Type::IDrawableUP& o, Mode m, Args... args)
{
	auto& c = dynamic_cast<T&>(*o);
	if (m == Mode::Do) changeObjectSpecifically(c, S(), nbCalls, args...);
	else changeObjectSpecifically(c, S().mirror(), nbCalls, args...);
}

template <typename T, typename F, typename ... Args>
void Behaviour::changeObjectSpecifically(T& o, F f, std::size_t nbCalls, Args... args)
{
	for (std::size_t i = 0; i < nbCalls; ++i)
			(o.*f.get())(args...);
}
