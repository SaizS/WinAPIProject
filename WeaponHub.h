#pragma once

class WeaponHub
{
private:
	Image* weapon;
	Rect* rect;

	vector<Image*> numbers;

	//vector<Image*> bulletNum;
	//vector<Rect*> bulletRect;
	Image* basicBullet;
	Rect* basicRect;

	vector<Image*> frameNum;
	vector<Rect*> frameRect;

	vector<Image*> bombNum;
	vector<Rect*> bombRect;

public:
	WeaponHub();
	~WeaponHub();

	void Render(HDC hdc);

	void SetNumber(Player* player);
	void SetFrameNumber(Player* player);
};