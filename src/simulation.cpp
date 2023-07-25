#pragma once
#include "simulation.h"
#include "wall.h"
#include <iostream>

Simulation::Simulation(int width, int height) : _height(height), _width(width)
{
	// Seed rng
	std::srand(unsigned(std::time(0)));

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(_width, _height, 0, &_window, &_renderer);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);
	SDL_RenderPresent(_renderer);
}

Simulation::~Simulation()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Simulation::clear()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);
}

void Simulation::draw_rect(int x, int y, int w, int h, SDL_Colour colour)
{
	SDL_SetRenderDrawColor(_renderer, colour.r, colour.g, colour.b, colour.a);
	
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	
	SDL_RenderFillRect(_renderer, &r);
	//SDL_RenderDrawRect(_renderer, &r);
	//SDL_RenderPresent(_renderer);
}

void Simulation::draw_rect(SDL_Rect rect, SDL_Colour colour)
{
	SDL_SetRenderDrawColor(_renderer, colour.r, colour.g, colour.b, colour.a);

	SDL_RenderFillRect(_renderer, &rect);
	//SDL_RenderDrawRect(_renderer, &r);
	//SDL_RenderPresent(_renderer);
}

void Simulation::draw_walls(Wall walls[])
{
	for (int i = 0; i <= sizeof(walls); i++)
	{
		draw_rect(walls[i].rect, walls[i].colour);
	}
}

int Simulation::get_random_pos(int lower, int upper)
{
	return (std::rand() % upper) + lower;
}

void Simulation::Run()
{
	SDL_Event event;
	SDL_Rect r = { .x = 100, .y = 100, .w=10, .h=100 };
	//Wall wall(r, GREY, "wall");
	Wall walls[4] = {Wall(r = {.x = 100, .y = 100, .w = 10, .h = 100}, GREY, "wall"),
		Wall(r={.x = 200, .y = 100, .w = 100, .h = 10}, GREY, "wall"),
		Wall(r={.x = 540, .y = 100, .w = 10, .h = 100}, GREY, "wall"),
		Wall(r={.x = 0, .y = 240, .w = 20, .h = 20}, WHITE, "wb") };
	
	while (1)
	{
		SDL_Delay(16);
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT)
			break;
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				break;
		}
		
		clear();
		
		draw_rect(10, 10, 50, 50, RED);
		//draw_rect(wall.rect, wall.colour);
		draw_walls(walls);

		// Place resource
		if (resources.size() < 4)
			resources.push_back(Resource(r = { .x = get_random_pos(0, _width - 10), .y = get_random_pos(0, _height - 10), .w = rectSize, .h = rectSize }, GREEN));

		for (Resource res : resources)
		{
			draw_rect(res.rect.x, res.rect.y, res.rect.w, res.rect.h, res.colour);
		}

		SDL_RenderPresent(_renderer);
	}
}
