#include <iostream>
using namespace std;

// Vector2.h
class Vector2
{
public:
	Vector2() = default;

	Vector2(const float x, const float y);

	void operator=(const Vector2& other);

	Vector2 operator*(const float other) const;
	
	friend Vector2 operator*(const float other, const Vector2& vec);

	friend ostream& operator<<(ostream& os, const Vector2& vec);

	void Print() const;

public:
	float x, y;
};


// Vector2.cpp
Vector2::Vector2(const float x, const float y)
	: x(x), y(y)
{}

void Vector2::operator=(const Vector2 & other)
{
	x = other.x;
	y = other.y;
}

Vector2 Vector2::operator*(const float other) const
{
	return Vector2(x * other, y * other);
}

Vector2 operator*(const float other, const Vector2& vec)
{
	return vec * other;
}

ostream& operator<<(ostream& os, const Vector2& vec)
{
	vec.Print();
	return os;
}

void Vector2::Print() const
{
	cout << x << ", " << y << endl;
}


int main()
{
	Vector2 a;
	a.x = 2.0f; a.y = 3.0f;

	// a = a * 2.3f;
	a = 2.3f * a;


	a.Print();
	cout << a << a;

	return 0;
}