#pragma once

class PlayScene : public Scene
{
private:
	Player* player;
	EnemyManager* em;
	BackGround* bg;
	HubManager* hm;
	Npc* npc;

	Image* colllsionLand;

public:
	PlayScene();
	~PlayScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void LoadSound();
	void LoadEffect();
};