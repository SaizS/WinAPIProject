#pragma once

class Tank
{
private:
	enum TankDirection
	{
		IDLE,
		READY,
		FIRE,
		HIT,
		MOVE,
		DESTROY
	};
	vector<Image*> leftImages;
	vector<Animation*> leftAnis;

	vector<Image*> rightImages;
	vector<Animation*> rightAnis;

	Image* curImage;
	Animation* curAni;

	Rect* rect;

	int hp;

	float attackTime;
	float delay;
	float spawnTime;

	bool isFire;

	vector<TankBullet*> bullets;

	bool isActive;
	bool isDie;
	bool isRight;

	float resetTime;
public:
	Tank();
	~Tank();

	void Update();
	void Render(HDC hdc);

	void Load();

	void SetDir(TankDirection dir);
	void Fire();
	void SetIsFire() { isFire = false; }
	void SetIdle();

	Rect GetRect() { return *rect; }

	void Damage(int damage);

	bool GetIsActive() { return isActive; }

	vector<TankBullet*> GetTankBullet() { return bullets; }

	void Play();
	void Left();
	void Right();
};