#include <iostream>
#include <thread>
#include <QApplication>

#include <Core/GifCreator.hpp>
#include <Core/ConcreteObjects/Square.hpp>
#include <Core/Behaviour.hpp>
#include <Core/Type.hpp>
#include <Registrar/Registrar.hpp>

static void testDecode();
static void createSampleGif();

int main()
{
	std::thread t0(testDecode);
	std::thread t1(createSampleGif);

	t0.join();
	t1.join();
}

static void testDecode()
{
	Registrar d;
	const auto gp = d.registerGifParameters();
	GifCreator gc1(gp.width, gp.height, gp.nbFrames, gp.delay);
	auto os = d.registerObjects();
	for (auto& o : os)
		gc1.registerObject(std::move(o));
	auto bs = d.registerBehaviours();
	for (auto& b : bs)
		gc1.registerBehaviour(std::move(b));
	const auto as = d.registerApplications();
	for (const auto& a : as)
		a(gc1);
	const auto testDecodeFileName = "testDecode.gif";
	gc1.createGif(testDecodeFileName);
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
		gc.registerObject(std::make_unique<Square>(name));
		gc.registerObject(std::make_unique<Square>(name1));
		gc.registerObject(std::make_unique<Square>(name2));
	}

	{
		const auto singleStep = 1;
		const auto beginning = 0;
		const auto bName = "initial";
		auto initial = std::make_unique<Behaviour>(bName, singleStep);
		initial->at<IPositionable, IPositionable::gotoCenter>(beginning);
		initial->at<IColorable, IColorable::setColor>(beginning, BasicColors::red);
		gc.registerBehaviour(std::move(initial));
		gc.setDoBehaviourForAt(bName, name, beginning);
	}

	{
		const auto singleStep = 1;
		const auto beginning = 0;
		const auto nbCalls = 100;
		const auto bName = "initial2";
		auto initial = std::make_unique<Behaviour>(bName, singleStep);
		initial->at<IPositionable, IPositionable::gotoCenter>(beginning);
		initial->at<IMovable, IMovable::moveLeft, nbCalls>(beginning);
		initial->at<IMovable, IMovable::moveUp, nbCalls>(beginning);
		initial->at<IColorable, IColorable::setColor>(beginning, BasicColors::green);
		gc.registerBehaviour(std::move(initial));
		gc.setDoBehaviourForAt(bName, name1, beginning);
	}

	{
		const auto singleStep = 1;
		const auto beginning = 0;
		const auto nbCalls = 100;
		const auto bName = "initial3";
		auto initial = std::make_unique<Behaviour>(bName, singleStep);
		initial->at<IPositionable, IPositionable::gotoCenter>(beginning);
		initial->at<IMovable, IMovable::moveRight, nbCalls>(beginning);
		initial->at<IMovable, IMovable::moveDown, nbCalls>(beginning);
		initial->at<IColorable, IColorable::setColor>(beginning, BasicColors::blue);
		gc.registerBehaviour(std::move(initial));
		gc.setDoBehaviourForAt(bName, name2, beginning);
	}

	{
		const auto halfNbFrames = nbFrames / 2;
		const auto quarterNbFrames = halfNbFrames / 2;
		const auto beginning = 0;
		const auto nbCalls = 6;
		const auto rate = 3;
		const auto bName = "general";
		auto b = std::make_unique<Behaviour>(bName, halfNbFrames);
		b->fromTill<IMovable, IMovable::moveRight>(0, quarterNbFrames);
		b->from<IMovable, IMovable::moveDown>(beginning);
		b->from<IMovable, IMovable::moveUp, nbCalls>(beginning);
		b->from<IMovable, IMovable::moveDown, nbCalls * rate>(quarterNbFrames);
		b->from<IMovable, IMovable::moveLeft, nbCalls>(quarterNbFrames);
		b->till<IZoomable, IZoomable::zoomIn, nbCalls>(quarterNbFrames);
		gc.registerBehaviour(std::move(b));
		gc.setDoBehaviourForAt(bName, name, beginning + 1);
		gc.setUndoBehaviourForAt(bName, name, halfNbFrames);
		gc.setDoBehaviourForAt(bName, name1, beginning + 1);
		gc.setUndoBehaviourForAt(bName, name1, halfNbFrames);
		gc.setDoBehaviourForAt(bName, name2, beginning + 1);
		gc.setUndoBehaviourForAt(bName, name2, halfNbFrames);
	}

	gc.createGif();
}
