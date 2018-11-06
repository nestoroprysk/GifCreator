#include "GifCreator.hpp"

int main()
{
	const auto width = 100;
	const auto height = 100;
	GifCreator gc(width, height);
	gc.drawBlackAndWhiteFrames();
}
