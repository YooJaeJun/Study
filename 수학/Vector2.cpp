#include <math.h>
#include <Turboc.h>
class vector2 {
public:
	float x, y;
	vector2(float new_x, float new_y);
	vector2();
	vector2 get_normalize() const;
	vector2 plus(const vector2& other) const;
	vector2 minus(const vector2& other) const;
	vector2 multiple(const vector2& other) const;
	float dot(const vector2& other) const;
	float length_sq(const vector2& other) const;
	float length(const vector2& other) const;
	vector2 multiple_float(const float & other) const;
};
vector2 vector2::get_normalize() const
{
	float sq = sqrt(x*x + y * y);
	return vector2(x / sq, y / sq);
}
vector2 vector2::plus(const vector2& other) const
{
	return vector2(x + other.x, y + other.y);
}
vector2 vector2::minus(const vector2& other) const
{
	return vector2(x - other.x, y - other.y);
}
vector2 vector2::multiple(const vector2& other) const
{
	return vector2(x * other.x, y * other.y);
}
float vector2::dot(const vector2& other) const
{
	return (x * other.x + y * other.y);
}
float vector2::length_sq(const vector2& other) const
{
	return vector2::dot(other);
}
float vector2::length(const vector2& other) const
{
	return sqrt(vector2::length_sq(other));
}
//½ºÄ®¶ó °öÇÏ±â º¤ÅÍ. f°¡ ½ºÄ®¶ó
vector2 vector2::multiple_float(const float &f) const
{
	return vector2(x * f, y * f);
}
void main()
{
	vector2 v0 = { 1.0f, 0.0f };
	v0.multiple_float(5.0);
	float value = v0.dot(v0);
	printf("%f", value);
}