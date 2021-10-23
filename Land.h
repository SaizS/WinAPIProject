#pragma once

class Land
{
private:
	Image* land;
	Rect* rect;

public:
	Land();
	~Land();

	void Render(HDC hdc);
	void MoveMap(float val);
	Rect GetRect() { return *rect; }
};