
struct Vec2
{
	float x;
	float y;

	void rotate(float angle, Vec2 center);
	float magnitude();
	void normalise();
	Vec2 subtract(Vec2 a, Vec2 b);
	void scale_to_length(float length);
};
