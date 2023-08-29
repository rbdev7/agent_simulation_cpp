#pragma once
#include <SDL.h>
#include <vector>
#include "wall.h"
#include "resource.h"
#include "agent.h"

class Simulation
{
public:
	Simulation(int height, int width);
	
	~Simulation();

	void Run();

	void clear();

private:
	int m_height;
	int m_width;
	bool mIsRunning = false;
	bool mShowVector = true;
	int mVectorScale = 25;
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	const SDL_Colour RED = { .r = 255, .g = 0, .b = 0 };
	const SDL_Colour YELLOW = { .r = 255, .g = 255, .b = 0 };
	const SDL_Colour BLUE = { .r = 0, .g = 0, .b = 255 };
	const SDL_Colour GREEN = { .r = 0, .g = 255, .b = 0 };
	const SDL_Colour GREY = { .r = 100, .g = 100, .b = 100 };
	const SDL_Colour BLACK = { .r = 0, .g = 0, .b = 0 };
	const SDL_Colour WHITE = { .r = 255, .g = 255, .b = 255 };
	const int FPS = 60;
	const int FRAME_DELAY = 1000 / FPS;
	Uint32 m_frameStart;
	int m_frameTime;
	int m_rectSize = 10;
	int m_maxAgents = 10;
	int m_agentSpeed = 1;
	float m_agentForce = 0.4;
	std::vector<Wall> m_walls;
	std::vector<Resource> m_resources;
	std::vector<Agent> m_agents;

	void draw_rect(int x, int y, int w, int h, SDL_Colour colour);
	void draw_rect(SDL_Rect rect, SDL_Colour colour);
	void draw_line(Vec2 pos, Vec2 end, SDL_Colour colour, int width);
	void draw_walls();
	void draw_agents();
	void draw_resources();
	int get_random_pos(int lower, int upper);
	void createWalls();
	void createAgents();
	void handelEvents();
	void update();
	void render();
};


