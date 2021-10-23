#pragma once

class Bomb
{
private:
	Image* bomb;
	Animation* bombAni;
	Rect* rect;
	int damage;

	Image* land;

	float angle;
	float speed;
	float gravity;
	Vector realPos;

	bool isActive;
	bool isBounce;
public:
	Bomb();
	~Bomb();

	void Update();
	void Render(HDC hdc);

	void PlayBomb(float angle, Vector pos, Vector fullPos);
	float GetLandY();

	bool GetIsActive() { return isActive; }
	void SetIsActive() { isActive = false; }

	int GetDamage() { return damage; }

	Rect GetRect() { return *rect; }
};