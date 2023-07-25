#pragma once
#include <SDL_rect.h>
#include <string>

class Resource
{
public:
	SDL_Rect rect;
	SDL_Colour colour;
	std::string type = "resource";

	Resource(SDL_Rect r, SDL_Colour c);
};
