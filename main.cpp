#include "GifCreator.hpp"
#include "Irregular.hpp"

int main()
{
	const auto width = 10;
	const auto height = 10;
	const auto delay = 1;
	GifCreator gc(width, height, delay);
	{
		std::unique_ptr<IDrawable> p = std::make_unique<Irregular>(
			std::vector<Pixel>{
							Pixel{1, 0, BasicColors::green},
		 					Pixel{3, 0, BasicColors::green},
		 					Pixel{0, 2, BasicColors::green},
		 					Pixel{1, 3, BasicColors::green},
		 					Pixel{2, 3, BasicColors::green},
		 					Pixel{3, 3, BasicColors::green},
		 					Pixel{4, 2, BasicColors::green}});
		gc.registerObject(std::move(p));
	}
	const auto nbFrames = 10;
	for (std::size_t i = 0; i < nbFrames; ++i)
		gc.makeFrame();
}
