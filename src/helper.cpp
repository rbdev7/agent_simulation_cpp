#pragma once
#include "helper.h"
#include <cmath>

void Vec2::rotate(float angle, Vec2 center)
{
	float dx = center.x;
	float dy = center.y;
	
	x = ((x - dx) * std::cos(angle)) - ((dy - y) * sin(angle)) + dx;
	y = dy - ((dy - y) * std::cos(angle)) + ((x - dx) * std::sin(angle));

	normalise();
}

void Vec2::normalise()
{
	float magnitude = sqrt(pow(x,2) + pow(y,2));
	x = x / magnitude;
	y = y / magnitude;
}
