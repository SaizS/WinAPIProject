#include "framework.h"

Vector::Vector() : x(0.0f), y(0.0f)
{
}

Vector::Vector(float x, float y) : x(x), y(y)
{
}

Vector Vector::operator+(const Vector& val) const
{	
	return Vector(x + val.x, y + val.y);
}

Vector Vector::operator-(const Vector& val) const
{
	return Vector(x - val.x, y - val.y);
}

Vector Vector::operator*(const float& val) const
{
	return Vector(x * val, y * val);
}

void Vector::operator+=(const Vector& val)
{
	x += val.x;
	y += val.y;
}

void Vector::operator-=(const Vector& val)
{
	x -= val.x;
	y -= val.y;
}

void Vector::operator*=(const float& val)
{
	x *= val;
	y *= val;
}

bool Vector::operator==(const Vector& val)
{
	if (x == val.x && y == val.y)
		return true;

	return false;
}

void Vector::Normalize()
{
	x /= Length();
	y /= Length();
}

Vector Vector::GetNormalize() const
{	
	return Vector(x / Length(), y / Length());
}

float Vector::Length() const
{
	return sqrt(x * x + y * y);
}
