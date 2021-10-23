#pragma once

class Bullet
{
private:
	Image* image[2];
	Rect* rect[2];
	int damage;
	float speed;

	bool isActive;
	bool isRight;
	bool isUp;
public:
	Bullet();
	~Bullet();

	void Update();
	void Render(HDC hdc);
	void Fire(Vector pos, bool Right, bool Up);

	bool GetIsActive() { return isActive; }
	Rect GetRect();

	void SetIsActive() { isActive = false; }

	int GetDamage() { return damage; }
};