#include "GifCreator.hpp"
#include "Square.hpp"
#include "Behaviour.hpp"
#include "Utils.hpp"

int main()
{
	const auto width = 500;
	const auto height = 500;
	const auto nbFrames = 50;
	const auto delay = 10;
	GifCreator gc(width, height, nbFrames, delay);
	const auto name = "SampleSquare";
	const auto name1 = "SampleSquare1";
	const auto name2 = "SampleSquare2";
	const auto name3 = "SampleSquare3";
	gc.registerObject(name, std::make_unique<Square>());
	gc.registerObject(name1, std::make_unique<Square>());
	gc.registerObject(name2, std::make_unique<Square>());
	gc.registerObject(name3, std::make_unique<Square>());
	Behaviour b(nbFrames);
	b.at(0, &IMovable::gotoCenter);
	b.till(25, &IZoomable::zoomIn);
	b.fromTill(25, 50, &IZoomable::zoomOut);
	gc.setBehaviour(name, b);
	gc.setBehaviour(name1, b);
	gc.setBehaviour(name2, b);
	gc.setBehaviour(name3, b);
	Behaviour s(nbFrames);
	s.till(nbFrames, &IMovable::moveLeft);
	s.till(nbFrames, &IMovable::moveDown);
	s.till(nbFrames, &IMovable::moveDown);
	s.till(nbFrames, &IMovable::moveDown);
	gc.setBehaviour(name, s);
	Behaviour s1(nbFrames);
	s1.at(0, &IColorable::setColor, BasicColors::red);
	s1.till(nbFrames, &IMovable::moveLeft);
	s1.till(nbFrames, &IMovable::moveUp);
	s1.till(nbFrames, &IMovable::moveUp);
	s1.till(nbFrames, &IMovable::moveUp);
	gc.setBehaviour(name1, s1);
	Behaviour s2(nbFrames);
	s2.at(0, &IColorable::setColor, BasicColors::green);
	s2.till(nbFrames, &IMovable::moveRight);
	s2.till(nbFrames, &IMovable::moveRight);
	s2.till(nbFrames, &IMovable::moveRight);
	s2.till(nbFrames, &IMovable::moveUp);
	gc.setBehaviour(name2, s2);
	Behaviour s3(nbFrames);
	s3.at(0, &IColorable::setColor, BasicColors::blue);
	for (std::size_t i = 1; i < nbFrames; ++i)
		s3.till(nbFrames / i, &IMovable::moveRight);
	gc.setBehaviour(name3, s3);
	gc.createGif();
}
