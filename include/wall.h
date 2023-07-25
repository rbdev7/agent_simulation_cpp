#pragma once
#include <SDL.h>
#include <string>

class Wall
{
public:
	SDL_Rect rect;
	SDL_Colour colour;
	std::string type;

	Wall(SDL_Rect r, SDL_Colour c, std::string t);
};
