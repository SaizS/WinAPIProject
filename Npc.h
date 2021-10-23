#pragma once

class Npc
{
private:
	enum NpcDirection
	{
		IDLE = 0,
		UP,
		RWORKING,
		LWORKING,
		GIVE,
		BYE,
		RUN
	};

	vector<Image*> images;
	vector<Animation*> anis;
	Rect* rect;

	Image* curImage;
	Animation* curAni;

	bool isActive;

	float turnTime;
	float spawnTime;

	Player* player;
	FrameItem* frameItem;
	BombItem* bombItem;
public:
	Npc();
	~Npc();

	void Update();
	void Render(HDC hdc);

	void SetPlayer(Player* player) { this->player = player; }
	void SetDir(NpcDirection dir);
	void SetLWorking() { SetDir(LWORKING); }
	void SetBye();
	void SetRun() { SetDir(RUN); }

	void Give();
	void Spawn();
};