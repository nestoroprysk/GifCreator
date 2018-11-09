#include "GifCreator.hpp"
#include "Square.hpp"

int main()
{
	const auto width = 100;
	const auto height = 100;
	const auto delay = 10;
	GifCreator gc(width, height, delay);
	const auto name = "SampleSquare";
	gc.registerObject(name, std::make_unique<Square>());
	gc.changeObject(name, &IMovable::gotoCenter);
	const auto nbFrames = 10;
	const auto nbZooms = 5;
	for (std::size_t i = 0; i < nbFrames; ++i){
		for (std::size_t j = 0; j < nbZooms; ++j)
			gc.changeObject(name, &IZoomable::zoomIn);
		gc.makeFrame();
	}
}
