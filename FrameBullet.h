#pragma once

class FrameBullet
{
private:
	enum FrameDir
	{
		RIGHT,
		LEFT,
		UP
	};

	Image* image[3];
	Animation* ani[3];
	Rect* rect;
	Rect* upRect;
	Rect* hitBox;

	bool isActive;
	bool isRight;
	bool isUp;
public:
	FrameBullet();
	~FrameBullet();

	void Update();
	void Render(HDC hdc);

	void Fire(Vector pos, bool isRight, bool isUp);

	void SetIsActive();

	bool GetIsActive() { return isActive; }

	Rect GetRect() { return *hitBox; }

	int GetFrame();
};