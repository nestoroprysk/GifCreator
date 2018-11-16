#pragma once
#include <unordered_map>
#include <string>
#include "Behaviour.hpp"

class Image;
class IDrawable;
class GifWriterHandle;
class Color;
class ChangeSetType;

class GifCreator
{
private:
	static constexpr std::uint32_t defaultDelay_ = 10;
	static constexpr auto defaultFileName_ = "new.gif";

private:
	using BehaviorGet = auto (Behaviour::*)() const -> const Behaviour::ChangeSetType &;
	using ImageUP = std::unique_ptr<Image>;
	using IDrawableUP = std::unique_ptr<IDrawable>;

public:
	GifCreator(std::uint32_t width, std::uint32_t height, std::size_t nbFrames,
		std::uint32_t delay = defaultDelay_);
	void registerObject(std::unique_ptr<IDrawable>&&, const std::string& uniqueName);
	void setDoBehaviourAt(std::size_t, const std::string& objectName, const Behaviour&);
	void setUndoBehaviourAt(std::size_t, const std::string& objectName, const Behaviour&);
	void createGif(const std::string& fileName = defaultFileName_);
	~GifCreator();

private:
	void makeFrame(GifWriterHandle&);

private:
	GifCreator() = delete;

private:
	void updateImage();

private:
	void setSpecifiedBehaviourAt(std::size_t, const std::string& objectName, const Behaviour&, BehaviorGet);

private:
	ImageUP image_;
	const std::uint32_t width_;
	const std::uint32_t height_;
	const std::uint32_t delay_;
	const std::size_t nbFrames_;
	std::unordered_map<std::string, IDrawableUP> storage_;
	std::unordered_map<std::size_t, std::vector<std::function<void()>>> changes_;
	Type::ColorMatrix pixelMapper_;
};
