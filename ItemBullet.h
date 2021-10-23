#pragma once

class ItemBullet
{
private:
	Image* image[4];
	Rect* rect[4];
	bool isActive[4];

	float delayTime;
	float angle[4];
	float speed;

	bool isFire;

public:
	ItemBullet();
	~ItemBullet();

	void Update();
	void Render(HDC hdc);

	void Fire(Vector pos);

	void Setting();

	bool GetIsFire() { return isFire; }
	bool GetIsActive(int val) { return isActive[val]; }
	Rect* GetRect() { return *rect; }

	void SetIsActive(int count) { isActive[count] = false; }
};