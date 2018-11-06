#include "GifCreator.hpp"

int main()
{
	const auto width = 100;
	const auto height = 100;
	const auto delay = 1;
	GifCreator gc(width, height, delay);
	gc.drawMovingDot();
}
