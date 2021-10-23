#pragma once

#define BGCOUNT 3

class BackGround
{
private:
	Sky* sky;
	Land* land;

public:
	BackGround();
	~BackGround();

	void Update();
	void Render(HDC hdc);
	void MoveMap(float val);
	Rect GetRect() { return land->GetRect(); }
};