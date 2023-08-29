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
	velocity = Vec2(0, 0);
	desired = Vec2(0, 0);
	pos.x = r.x;
	pos.y = r.y;

	set_center();
	//velocity.rotate(rand() % 360, center);
}

void Agent::set_center()
{
	center.x = (rect.w / 2) + rect.x;
	center.y = (rect.h / 2) + rect.y;
}

Vec2 Agent::location()
{
	Vec2 location;
	location.x = rect.x;
	location.y = rect.y;

	return location;
}

void Agent::seek(Vec2 target)
{
	//Vec2 location;
	//location.x = rect.x;
	//location.y = rect.y;

	desired = Vec2().subtract(target, pos);
	desired.normalise();
	desired.x = desired.x * speed;
	desired.y = desired.y * speed;
	//desired.scale_to_length(speed);

	Vec2 steer = Vec2().subtract(desired, velocity);
	if (steer.magnitude() > force)
		steer.scale_to_length(force);
	acceleration.x = acceleration.x + steer.x;
	acceleration.y = acceleration.y + steer.y;
	//update();
}

void Agent::wander()
{
	Vec2 future;
	future.x = pos.x + (velocity.x * WANDER_CIRCLE_DIST);
	future.y = pos.y + (velocity.y * WANDER_CIRCLE_DIST);

	Vec2 rndVec(WANDER_CIRCLE_RADIUS, 0);
	set_center();
	rndVec.rotate(rand() % 360, center);
	//rndVec.x = -rndVec.x;

	Vec2 target;
	target.x = future.x + rndVec.x;
	target.y = future.y + rndVec.y;

	// Cap the vector to the bounds of the screen.
	if (target.x > 640)
		target.x = target.x - 640;
	if (target.y > 480)
		target.y = target.y - 480;

	seek(target);
}

void Agent::update()
{
	if (state == "wander")
		wander();

	velocity.x = velocity.x + acceleration.x;
	velocity.y = velocity.y + acceleration.y;

	if (acceleration.magnitude() == 0)
		velocity.scale_to_length(speed);
	if (velocity.magnitude() > speed)
		velocity.scale_to_length(speed);

	pos.x = pos.x + velocity.x;
	pos.y = pos.y + velocity.y;
	rect.x = (int)(pos.x);
	rect.y = (int)(pos.y);

	if (rect.x <= 0)
	{
		rect.x = 1;
		pos.x = 1;
	}
	if (rect.x+rect.w > bounds.x)
	{
		rect.x = (int)(bounds.x-rect.w);
		pos.x = rect.x;
	}
	if (rect.y <= 0)
	{
		rect.y = 1;
		pos.y = 1;
	}
	if (rect.y + rect.h > bounds.y)
	{
		rect.y = (int)(bounds.y - rect.h);
		pos.y = rect.y;
	}
}
