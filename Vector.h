#pragma once

struct Vector
{
	float x;
	float y;

	Vector();
	Vector(float x, float y);

	Vector operator+(const Vector& val) const;
	Vector operator-(const Vector& val) const;
	Vector operator*(const float& val) const;
	void operator+=(const Vector& val);
	void operator-=(const Vector& val);
	void operator*=(const float& val);
	bool operator==(const Vector& val);


	void Normalize();//자신을 단위백터로 만드는 함수
	Vector GetNormalize() const;//(변경없이)단위백터로 반환하는 함수

	float Length() const;
};