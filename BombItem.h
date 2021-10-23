#pragma once

class BombItem
{
private:
	Image* image;
	Animation* ani;
	Rect* rect;

	bool isActive;
public:
	BombItem();
	~BombItem();

	void Update();
	void Render(HDC hdc);

	void SetIsActiveFalse();
	void SetIsActiveTrue(Vector pos);
	bool Eat(Rect rc);
};