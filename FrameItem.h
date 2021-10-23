#pragma once

class FrameItem
{
private:
	Image* image;
	Rect* rect;

	bool isActive;

public:
	FrameItem();
	~FrameItem();

	void Render(HDC hdc);
	void SetIsActiveTrue(Vector pos);
	void SetIsActiveFalse() { isActive = false; }
	bool Eat(Rect rc);
};