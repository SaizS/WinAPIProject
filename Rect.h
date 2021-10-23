#pragma once

struct Rect
{
	Vector pos;
	Vector size;

	Rect();
	Rect(float x, float y, float width, float height);
	Rect(Vector pos, Vector size);	

	void SetRect(float left, float top, float right, float bottom);

	float Left() { return pos.x - size.x * 0.5f; }
	float Right() { return pos.x + size.x * 0.5f; }
	float Top() { return pos.y - size.y * 0.5f; }
	float Bottom() { return pos.y + size.y * 0.5f; }

	Vector HalfSize() { return Vector(size.x * 0.5f, size.y * 0.5f); }

	bool Collision(Rect rect);//단순 충돌검사
	bool Collision(Rect* rect);//매개변수로 받은 객체를 안겹치게 밀어내며 검사	
	bool Collision(Rect* dest, Rect* src);
	bool Collision(Vector pos);
};