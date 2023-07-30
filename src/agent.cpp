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

	// TODO: Set initial velocity to 0 and remove random direction.
	velocity = Vec2(0.01f, 0);
	set_center();
	velocity.rotate(rand() % 360, center);
}

void Agent::set_center()
{
	center.x = (rect.w / 2) + rect.x;
	center.y = (rect.h / 2) + rect.y;
}

void Agent::update()
{
	velocity.x = velocity.x + acceleration.x;
	velocity.y = velocity.y + acceleration.y;

	if (acceleration.magnitude() == 0)
		velocity.scale_to_length(speed);
	if (velocity.magnitude() > speed)
		velocity.scale_to_length(speed);

	rect.x = rect.x + (int)(velocity.x * 2);
	rect.y = rect.y + (int)(velocity.y * 2);

	if (rect.x <= 0)
	{
		rect.x = 1;
	}
	if (rect.x+rect.w > bounds.x)
	{
		rect.x = (int)(bounds.x-rect.w);
	}
	if (rect.y <= 0)
	{
		rect.y = 1;
	}
	if (rect.y + rect.h > bounds.y)
	{
		rect.y = (int)(bounds.y - rect.h);
	}
}
