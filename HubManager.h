#pragma once

class HubManager
{
private:
	ScoreHub* score;
	WeaponHub* weapon;

	Player* player;
public:
	HubManager();
	~HubManager();

	void Update();
	void Render(HDC hdc);
	void SetPlayer(Player* player) { this->player = player; }
};