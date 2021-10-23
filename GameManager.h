#pragma once
class GameManager
{
private:
	/*Player* player;
	EnemyManager* em;
	BackGround* bg;
	HubManager* hm;
	Npc* npc;

	Image* colllsionLand;*/

	HDC memDC;
	HBITMAP hBit;
public:
	GameManager();
	~GameManager();

	void Update();
	void Render(HDC hdc);

	void LoadSound();
	void LoadEffect();
};

