#pragma once

class TankBullet
{
private:
	Image* image[2];
	Animation* ani[2];
	Rect* rect;

	float speed;

	bool isActive;
	bool isRight;
public:
	TankBullet();
	~TankBullet();

	void Update();
	void Render(HDC hdc);

	void Fire(Vector pos, bool isRight);

	bool GetIsActive() { return isActive; }
	void SetIsActive() { isActive = false; }

	Rect GetRect() { return *rect; }
};