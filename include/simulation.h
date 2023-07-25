#pragma once
#include <SDL.h>
#include "wall.h"

class Simulation
{
public:
	Simulation(int height, int width);
	
	~Simulation();

	void Run();

	void clear();

	void draw_rect(int x, int y, int w, int h, SDL_Colour colour);
	void draw_rect(SDL_Rect rect, SDL_Colour colour);
	void draw_walls(Wall walls[]);

private:
	int _height;
	int _width;
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	const SDL_Colour RED = { .r = 255, .g = 0, .b = 0 };
	const SDL_Colour YELLOW = { .r = 255, .g = 255, .b = 0 };
	const SDL_Colour BLUE = { .r = 0, .g = 0, .b = 255 };
	const SDL_Colour GREEN = { .r = 0, .g = 255, .b = 0 };
	const SDL_Colour GREY = { .r = 100, .g = 100, .b = 100 };
	const SDL_Colour BLACK = { .r = 0, .g = 0, .b = 0 };
	const SDL_Colour WHITE = { .r = 255, .g = 255, .b = 255 };
};