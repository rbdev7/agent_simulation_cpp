#include "agent.h"

Agent::Agent(SDL_Rect r, SDL_Colour c, int speed, float force, std::string state, std::string type, Vec2 bounds)
	: rect(r),
	colour(c),
	speed(speed),
	force(force),
	state(state),
	type(type),
	bounds(bounds)
{
	acceleration = Vec2(0, 0);
	velocity = Vec2(1, 0);
	velocity.rotate(rand() % 360, center);
}

void Agent::set_center()
{
	center.x = (rect.w / 2) + rect.x;
	center.y = (rect.h / 2) + rect.y;
}

void Agent::update()
{
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;

	rect.x += velocity.x;
	rect.y += velocity.y;

	if (rect.x <= 0)
	{
		rect.x = 1;
	}
	if (rect.x+rect.w > bounds.x)
	{
		rect.x = bounds.x-rect.w;
	}
	if (rect.y <= 0)
	{
		rect.y = 1;
	}
	if (rect.y + rect.h > bounds.y)
	{
		rect.y = bounds.y - rect.h;
	}
}
