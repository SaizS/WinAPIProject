#pragma once

class Effect
{
private:
	Image* texture;
	Animation* ani;
	Rect* rect;

	bool isActive;
public:
	Effect(Image* texture, Vector size, float speed = 0.1f);
	~Effect();

	void Update();
	void Render(HDC hdc);

	void Start(Vector pos);
	void End();

	bool GetIsActive() {return isActive;}
};