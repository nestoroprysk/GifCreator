#include "GifCreator.hpp"
#include "Square.hpp"

int main()
{
	const auto width = 500;
	const auto height = 500;
	const auto nbFrames = 50;
	const auto delay = 10;
	GifCreator gc(width, height, nbFrames, delay);
	{
		const auto name = "SampleSquare";
		gc.registerObject(name, std::make_unique<Square>());
		gc.changeObjectAt(0, name, &IColorable::setColor, BasicColors::blue);
		gc.changeObjectAt(25, name, &IMovable::gotoCenter);
		gc.changeObjectTill(30, name, &IZoomable::zoomIn);
		gc.changeObjectAt(40, name, &IColorable::setColor, BasicColors::green);
		gc.changeObjectFrom(40, name, &IZoomable::zoomOut);
		gc.changeObjectFromTill(30, 40, name, &IMovable::moveUp);
	}
	{
		const auto name = "SampleSquare2";
		gc.registerObject(name, std::make_unique<Square>());
		gc.changeObjectAt(0, name, &IColorable::setColor, BasicColors::red);
		gc.changeObjectAt(0, name, &IMovable::gotoCenter);
		gc.changeObjectTill(30, name, &IZoomable::zoomIn);
		gc.changeObjectFrom(40, name, &IZoomable::zoomOut);
		gc.changeObjectFromTill(30, 40, name, &IMovable::moveDown);
		gc.changeObjectFromTill(0, 50, name, &IMovable::moveRight);
	}
	gc.createGif();
}
