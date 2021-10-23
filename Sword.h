#pragma once

class Sword
{
private:
	Image* image;
	Animation* ani;
	Rect* rect;

	Image* land;

	Vector pos;

	float angle;
	float speed;
	float gravity;

	bool isActive;
	bool isLast;

public:
	Sword();
	~Sword();

	void Update();
	void Render(HDC hdc);

	bool GetIsLast() { return isLast; }

	void Play(Vector pos, float angle, float gravity);

	float GetLandY();
	Rect GetRect();

	bool GetIsActive() { return isActive; }
	void SetIsActive() { isActive = false; }

	float GetGravity() { return gravity; }
	void Move(float val) { rect->pos.x -= val; }
};