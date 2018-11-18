#pragma once

#include <unordered_map>
#include <string>

#include "Type.hpp"
#include "Behaviour.hpp"

class Image;
class INameable;
class GifWriterHandle;
struct Color;
class ChangeSetType;

class GifCreator
{
private:
	static constexpr std::uint32_t defaultDelay_ = 10;
	static constexpr auto defaultFileName_ = "new.gif";

private:
	using BehaviorGet = auto (Behaviour::*)() const -> const Behaviour::ChangeSetType &;
	using ImageUP = std::unique_ptr<Image>;

public:
	GifCreator(std::uint32_t width, std::uint32_t height, std::size_t nbFrames,
		std::uint32_t delay = defaultDelay_);
	void registerObject(Type::INameableUP&&);
	void registerBehaviour(Type::BehaviourUP&&);
	void setDoBehaviourForAt(const std::string& behaviourName, const std::string& objectName, std::size_t);
	void setUndoBehaviourForAt(const std::string& behaviourName, const std::string& objectName, std::size_t);
	void createGif(const std::string& fileName = defaultFileName_);
	~GifCreator();

private:
	void makeFrame(GifWriterHandle&);

private:
	void updateImage();

private:
	void setSpecifiedBehaviourAt(const std::string& behaviourName, const std::string& objectName, std::size_t, BehaviorGet f);

private:
	ImageUP image_;
	const std::uint32_t width_;
	const std::uint32_t height_;
	const std::uint32_t delay_;
	const std::size_t nbFrames_;
	std::unordered_map<std::string, Type::IDrawableUP> objectStorage_;
	std::unordered_map<std::string, Type::BehaviourUP> behaviourStorage_;
	std::unordered_map<std::size_t, std::vector<std::function<void()>>> changes_;
	Type::ColorMatrix pixelMapper_;
};
