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
	Vec2 pos;

	const int WANDER_CIRCLE_DIST = 150;
	const int WANDER_CIRCLE_RADIUS = 50;

	Agent(SDL_Rect r, SDL_Colour c, int speed, float force, std::string state, std::string type, Vec2 bounds);
	void set_center();
	Vec2 location();
	void seek(Vec2 target);
	void wander();
	void update();
};
