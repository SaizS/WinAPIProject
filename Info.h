#pragma once

class Info
{
protected:
	int hp;
	bool isActive;

public:
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Damage(int damage) = 0;
};