#include "framework.h"

HubManager::HubManager()
{
	score = new ScoreHub();
	weapon = new WeaponHub();
}

HubManager::~HubManager()
{
	delete score;
	delete weapon;
}

void HubManager::Update()
{
	score->SetScore();
	score->SetLife(player->GetLife());
	weapon->SetNumber(player);
	weapon->SetFrameNumber(player);
}

void HubManager::Render(HDC hdc)
{
	score->Render(hdc);
	weapon->Render(hdc);
}
