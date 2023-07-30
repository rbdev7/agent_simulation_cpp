
struct Vec2
{
	float x;
	float y;

	void rotate(float angle, Vec2 center);
	float magnitude();
	void normalise();
	void scale_to_length(float length);
};
