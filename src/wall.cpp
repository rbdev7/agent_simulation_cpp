#include "wall.h"

Wall::Wall(SDL_Rect r, SDL_Colour c, std::string t)
{
	rect = r;
	colour = c;
	type = t;
}
