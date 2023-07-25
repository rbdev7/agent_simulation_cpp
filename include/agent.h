#pragma once
#include <SDL_rect.h>
#include <string>
#include <helper.h>

class Agent
{
public:
	SDL_Rect rect;
	SDL_Colour colour;
	int speed;
	float force;
	Vec2 acceleration;
	Vec2 velocity;
	std::string state;
	std::string type;
	Vec2 bounds;
	Vec2 center;

	Agent(SDL_Rect r, SDL_Colour c, int speed, float force, std::string state, std::string type, Vec2 bounds);
	void set_center();
	void update();
};
