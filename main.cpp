#include "GifCreator.hpp"
#include "Square.hpp"
#include "Behaviour.hpp"
#include "Type.hpp"

int main()
{
	const auto width = 100;
	const auto height = 100;
	const auto nbFrames = 30;
	const auto delay = 30;

	GifCreator gc(width, height, nbFrames, delay);

	const auto name = "SampleSquare";
	
	{
		gc.registerObject(std::make_unique<Square>(), name);
	}

	{
		const auto singleStep = 1;
		const auto beginning = 0;
		Behaviour initial(singleStep);
		initial.at<IPositionable, IPositionable::gotoCenter>(beginning);
		gc.setDoBehaviourAt(beginning, name, initial);
	}

	{
		const auto halfNbFrames = nbFrames / 2;
		const auto beginning = 0;
		const auto nbCalls = 3;
		Behaviour b(halfNbFrames);
		b.fromTill<IMovable, IMovable::moveRight>(0, halfNbFrames);
		b.from<IMovable, IMovable::moveDown>(beginning);
		b.from<IMovable, IMovable::moveUp, nbCalls>(beginning);
		b.till<IZoomable, IZoomable::zoomIn>(halfNbFrames / 2);
		b.at<IColorable, IColorable::setColor>(halfNbFrames / 2, BasicColors::red);
		gc.setDoBehaviourAt(beginning + 1, name, b);
		gc.setUndoBehaviourAt(halfNbFrames, name, b);
	}

	gc.createGif();
}
