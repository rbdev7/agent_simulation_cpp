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

	createWalls();
	createAgents();
	
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

void Simulation::draw_walls()
{
	for (Wall wall : m_walls)
	{
		draw_rect(wall.rect, wall.colour);
	}
}

void Simulation::draw_agents()
{
	for (Agent agent : m_agents)
	{
		draw_rect(agent.rect, agent.colour);
	}
}

void Simulation::draw_resources()
{
	for (Resource resource : m_resources)
	{
		draw_rect(resource.rect, resource.colour);
	}
}

int Simulation::get_random_pos(int lower, int upper)
{
	return (std::rand() % upper) + lower;
}

void Simulation::createWalls()
{
	m_walls = { Wall(SDL_Rect {.x = 100, .y = 100, .w = 10, .h = 100}, GREY, "wall"),
		Wall(SDL_Rect {.x = 200, .y = 100, .w = 100, .h = 10}, GREY, "wall"),
		Wall(SDL_Rect {.x = 540, .y = 100, .w = 10, .h = 100}, GREY, "wall"),
		Wall(SDL_Rect {.x = 0, .y = 240, .w = 20, .h = 20}, WHITE, "wb") };
}

void Simulation::createAgents()
{
	for (int i = 0; i < 5; i++)
	{
		m_agents.push_back(Agent(SDL_Rect() = { .x = 320, .y = 240, .w = m_rectSize, .h = m_rectSize }, YELLOW, m_agentSpeed, m_agentForce, "wander", "grazer", Vec2() = { .x = (float)m_width, .y = (float)m_height }));
	}
}

void Simulation::handelEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT)
		mIsRunning = false;
	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			mIsRunning = false;
	}
}

void Simulation::update()
{
	// Agents
	for (Agent& agent : m_agents)
	{
		agent.update();
	}

	// Place resource
	if (m_resources.size() < 4)
		m_resources.push_back(Resource(SDL_Rect { .x = get_random_pos(0, m_width - 10), .y = get_random_pos(0, m_height - 10), .w = m_rectSize, .h = m_rectSize }, GREEN));
}

void Simulation::render()
{
	clear();

	// Walls
	draw_walls();

	// Resources
	draw_resources();

	// Agents
	draw_agents();

	SDL_RenderPresent(m_renderer);
}

void Simulation::Run()
{
	mIsRunning = true;

	while (mIsRunning)
	{
		m_frameStart = SDL_GetTicks();
		
		// Handel events
		handelEvents();

		
		
		//Update
		update();

		// Render
		render();

		//SDL_Delay(1000);
		m_frameTime = SDL_GetTicks() - m_frameStart;
		if (FRAME_DELAY > m_frameTime)
		{
			SDL_Delay(FRAME_DELAY - m_frameTime);
		}
	}
}
