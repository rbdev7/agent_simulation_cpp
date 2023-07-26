#pragma once
#include "simulation.h"
#include "wall.h"
#include <iostream>

Simulation::Simulation(int width, int height) : m_height(height), m_width(width)
{
	// Seed rng
	std::srand(unsigned(std::time(0)));

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(m_width, m_height, 0, &m_window, &m_renderer);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);
	SDL_RenderPresent(m_renderer);

	for (int i = 0; i < 10; i++)
	{
		m_agents.push_back(Agent(SDL_Rect() = { .x = 320, .y = 240, .w = m_rectSize, .h = m_rectSize }, YELLOW, m_agentSpeed, m_agentForce, "wander", "grazer",Vec2() = {.x = (float)m_width, .y = (float)m_height}));
	}
}

Simulation::~Simulation()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Simulation::clear()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);
}

void Simulation::draw_rect(int x, int y, int w, int h, SDL_Colour colour)
{
	SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
	
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	
	SDL_RenderFillRect(m_renderer, &r);
	//SDL_RenderDrawRect(_renderer, &r);
	//SDL_RenderPresent(_renderer);
}

void Simulation::draw_rect(SDL_Rect rect, SDL_Colour colour)
{
	SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);

	SDL_RenderFillRect(m_renderer, &rect);
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
		m_frameStart = SDL_GetTicks();
		
		//SDL_Delay(100);
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT)
			break;
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				break;
		}
		
		clear();

		// Agents
		for (Agent agent : m_agents)
		{
			agent.update();
			draw_rect(agent.rect.x, agent.rect.y, agent.rect.w, agent.rect.h, agent.colour);
		}
		
		draw_rect(10, 10, 50, 50, RED);
		//draw_rect(wall.rect, wall.colour);
		draw_walls(walls);

		// Place resource
		if (m_resources.size() < 4)
			m_resources.push_back(Resource(r = { .x = get_random_pos(0, m_width - 10), .y = get_random_pos(0, m_height - 10), .w = m_rectSize, .h = m_rectSize }, GREEN));

		for (Resource res : m_resources)
		{
			draw_rect(res.rect.x, res.rect.y, res.rect.w, res.rect.h, res.colour);
		}

		SDL_RenderPresent(m_renderer);

		m_frameTime = SDL_GetTicks() - m_frameStart;
		if (FRAME_DELAY > m_frameTime)
		{
			SDL_Delay(FRAME_DELAY - m_frameTime);
		}
	}
}
