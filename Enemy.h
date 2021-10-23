#pragma once

class Player;

class Enemy : public Info
{
private:
	enum EnemyDirection
	{
		LIDLE,
		LATK,
		LDIE1,
		LDIE2,
		RIDLE,
		RATK,
		RDIE
	};
	vector<Image*> images;
	vector<Animation*> anis;

	Image* curImage;
	Animation* curAni;

	Rect* rect;
	Vector pos;
	Rect* hitBox;

	Image* land;

	float attackDelay;
	
	float gravity;
	float attackTime;

	bool isDie;
	bool isRight;
	bool isAction;
	bool isSword;

	Sword* sword;

	Player* player;
public:
	Enemy();
	~Enemy();
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Damage(int damage) override;

	Rect GetHitBox() { return *hitBox; }

	bool GetIsActive() { return isActive; }

	float GetLandY();
	void SetY(float y);

	void Idle();
	void Attack();
	void Die();
	void Play(Rect rc);
	void Gravity();
	void SetIdle() { isAction = false; }
	void Move(float val) { rect->pos.x -= val; sword->Move(val); }

	Rect GetSwordRect() { return sword->GetRect(); }
	Sword* GetSword() { return sword; }
	bool GetIsDie() { return isDie; }

	void SetIsActive() { isActive = false; isDie = false; }
	void SetPlayer(Player* player) { this->player = player; }
	void SetAttackDelay();
};