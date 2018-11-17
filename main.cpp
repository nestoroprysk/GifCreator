#include <thread>
#include <QApplication>
#include <Core/GifCreator.hpp>
#include <Core/Square.hpp>
#include <Core/Behaviour.hpp>
#include <Core/Type.hpp>
#include <Gui/GifCreatorGui.hpp>

static void createSampleGif();

int main(int argc, char **argv)
{
	{
		std::thread t(createSampleGif);
		t.detach();
	}
	QApplication app(argc, argv);
	GifCreatorGui player;
	player.showFullScreen();
	return app.exec();
}

static void createSampleGif()
{
	const auto width = 500;
	const auto height = 500;
	const auto nbFrames = 120;
	const auto delay = 5;

	GifCreator gc(width, height, nbFrames, delay);

	const auto name = "SampleSquare";
	const auto name1 = "SampleSquare1";
	const auto name2 = "SampleSquare2";

	
	{
		gc.registerObject(std::make_unique<Square>(), name);
		gc.registerObject(std::make_unique<Square>(), name1);
		gc.registerObject(std::make_unique<Square>(), name2);
	}

	{
		const auto singleStep = 1;
		const auto beginning = 0;
		Behaviour initial(singleStep);
		initial.at<IPositionable, IPositionable::gotoCenter>(beginning);
		initial.at<IColorable, IColorable::setColor>(beginning, BasicColors::red);
		gc.setDoBehaviourAt(beginning, name, initial);
	}

	{
		const auto singleStep = 1;
		const auto beginning = 0;
		const auto nbCalls = 100;
		Behaviour initial(singleStep);
		initial.at<IPositionable, IPositionable::gotoCenter>(beginning);
		initial.at<IMovable, IMovable::moveLeft, nbCalls>(beginning);
		initial.at<IMovable, IMovable::moveUp, nbCalls>(beginning);
		initial.at<IColorable, IColorable::setColor>(beginning, BasicColors::green);
		gc.setDoBehaviourAt(beginning, name1, initial);
	}

	{
		const auto singleStep = 1;
		const auto beginning = 0;
		const auto nbCalls = 100;
		Behaviour initial(singleStep);
		initial.at<IPositionable, IPositionable::gotoCenter>(beginning);
		initial.at<IMovable, IMovable::moveRight, nbCalls>(beginning);
		initial.at<IMovable, IMovable::moveDown, nbCalls>(beginning);
		initial.at<IColorable, IColorable::setColor>(beginning, BasicColors::blue);
		gc.setDoBehaviourAt(beginning, name2, initial);
	}

	{
		const auto halfNbFrames = nbFrames / 2;
		const auto quarterNbFrames = halfNbFrames / 2;
		const auto beginning = 0;
		const auto nbCalls = 6;
		const auto rate = 3;
		Behaviour b(halfNbFrames);
		b.fromTill<IMovable, IMovable::moveRight>(0, quarterNbFrames);
		b.from<IMovable, IMovable::moveDown>(beginning);
		b.from<IMovable, IMovable::moveUp, nbCalls>(beginning);
		b.from<IMovable, IMovable::moveDown, nbCalls * rate>(quarterNbFrames);
		b.from<IMovable, IMovable::moveLeft, nbCalls>(quarterNbFrames);
		b.till<IZoomable, IZoomable::zoomIn, nbCalls>(quarterNbFrames);
		gc.setDoBehaviourAt(beginning + 1, name, b);
		gc.setUndoBehaviourAt(halfNbFrames, name, b);
		gc.setDoBehaviourAt(beginning + 1, name1, b);
		gc.setUndoBehaviourAt(halfNbFrames, name1, b);
		gc.setDoBehaviourAt(beginning + 1, name2, b);
		gc.setUndoBehaviourAt(halfNbFrames, name2, b);
	}

	gc.createGif();
}
