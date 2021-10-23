#pragma once

#define PLAYERSPEED 3.0f
#define GRAVITY 3.0f
#define JUMPPOWER 9.0f
#define BULLETCOUNT 200
#define BOMBCOUNT 20

class Player
{
private:
	enum Direction
	{
		RIDLE = 0,
		RRUN,
		LIDLE,
		LRUN,
		RJUMP,
		LJUMP,
		RFIRE,
		LFIRE,
		RBOMB,
		LBOMB,
		RATK,
		LATK,
		DIE,
		RUP,
		RUPIDLE,
		LUP,
		LUPIDLE,
		RUPFIRE,
		LUPFIRE,
		RDOWN,
		RDOWNIDLE,
		RDOWNMOVE,
		LDOWN,
		LDOWNIDLE,
		LDOWNMOVE,
		RDOWNFIRE,
		LDOWNFIRE,
		RDOWNATK,
		LDOWNATK,
		RDOWNBOMB,
		LDOWNBOMB,
		ITEMRIDLE,
		ITEMRRUN,
		ITEMRFIRE,
		ITEMLIDLE,
		ITEMLRUN,
		ITEMLFIRE,
		ITEMRUP,
		ITEMLUP,
		ITEMRUPFIRE,
		ITEMLUPFIRE,
		ITEMRBOMB,
		ITEMLBOMB,
		ITEMRDOWNIDLE,
		ITEMRDOWNMOVE,
		ITEMRDOWNFIRE,
		ITEMLDOWNIDLE,
		ITEMLDOWNMOVE,
		ITEMLDOWNFIRE,
		ITEMRDOWNATK,
		ITEMLDOWNATK,
		ITEMRDOWNBOMB,
		ITEMLDOWNBOMB
	};

	vector<Image*> upperBody;
	vector<Animation*> upperAni;

	vector<Image*> lowerBody;	
	vector<Animation*> lowerAni;

	Image* body[2];
	Animation* bodyAni[2];

	Rect* playerRect;
	Rect* hitBox;

	Vector pos;

	vector<Bullet*> bullets;
	vector<ItemBullet*> itemBullets;
	FrameBullet* frameBullet;
	vector<Bomb*> bombs;

	float jumpPower;
	float gravity;
	int resetTime;

	int damage;
	int life;
	int frameBulletCount;
	int bombCount;

	bool isRight;
	bool isMove;
	bool isJump;
	bool isAction;
	bool isDie;
	bool isUp;
	bool isDown;
	bool isItem;

	EnemyManager* em;

	Image* land;
	BackGround* bg;
public:
	Player();
	~Player();

	void Update();
	void Render(HDC hdc);

	void Move();
	void Jump();
	void Attack();
	void Map();

	void SetUp(Direction dir);
	void SetDown(Direction dir);
	void SetEnemy(EnemyManager* em) { this->em = em; }
	void SetCollision(Image* land) { this->land = land; }
	void SetBackGround(BackGround* bg) { this->bg = bg; }
	void SetAction() { isAction = false; isJump = false; }
	void SetIsUp() { isUp = true; }
	void SetIsDown() { isDown = true; }
	void SetDie();
	void SetItem() { isItem = true; }
 
	void BulletCollision();
	void BombCollision();

	float GetLandY();
	Rect GetRect() { return *hitBox; }
	FrameBullet* GetFrame() { return frameBullet; }
	int GetFrameBullet() { return frameBulletCount; }
	int GetBomb() { return bombCount; }
	int GetLife() { return life; }

	void InitUpperMotion();
	void InitLowerMotion();

	void Reset();

	vector<Bullet*> GetBullet() { return bullets; }
	void SetFrameBulletCount(int val) { frameBulletCount += val; }
	void SetBombCount(int val) { bombCount += val; }
	
};