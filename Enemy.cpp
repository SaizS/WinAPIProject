#include "framework.h"

Enemy::Enemy()
{
	hp = 10;
	isActive = false;

	Image* image;
	image = IMAGE->Add(L"Images/Enemy/Enemy - LeftRun.bmp", 1200, 100, 12, 1);
	images.push_back(image);
	anis.push_back(new Animation(image, 0.05f));

	image = IMAGE->Add(L"Images/Enemy/Enemy - LeftAttack1.bmp", 1900, 100, 19, 1);
	images.push_back(image);
	anis.push_back(new Animation(image, 0.08f));

	image = IMAGE->Add(L"Images/Enemy/Enemy - LeftDie1.bmp", 1400, 100, 14, 1);
	images.push_back(image);
	anis.push_back(new Animation(image, 0.05f));

	image = IMAGE->Add(L"Images/Enemy/Enemy - LeftDie2.bmp", 1300, 100, 13, 1);
	images.push_back(image);
	anis.push_back(new Animation(image, 0.05f));

	image = IMAGE->Add(L"Images/Enemy/Enemy - RightRun.bmp", 1200, 100, 12, 1);
	images.push_back(image);
	anis.push_back(new Animation(image, 0.05f));

	image = IMAGE->Add(L"Images/Enemy/Enemy - RightAttack1.bmp", 1900, 100, 19, 1);
	images.push_back(image);
	anis.push_back(new Animation(image, 0.08f));

	image = IMAGE->Add(L"Images/Enemy/Enemy - RightDie1.bmp", 1400, 100, 14, 1);
	images.push_back(image);
	anis.push_back(new Animation(image, 0.05f));

	anis[LIDLE]->SetDefault(true);
	anis[LATK]->SetDefault();
	anis[LATK]->SetEndEvent(bind(&Enemy::SetIdle, this));
	anis[LDIE1]->SetDefault();
	anis[LDIE1]->SetEndEvent(bind(&Enemy::SetIsActive, this));
	anis[LDIE2]->SetDefault();
	anis[LDIE2]->SetEndEvent(bind(&Enemy::SetIsActive, this));
	anis[RIDLE]->SetDefaultReverse(true);
	anis[RATK]->SetDefaultReverse();
	anis[RATK]->SetEndEvent(bind(&Enemy::SetIdle, this));
	anis[RDIE]->SetDefaultReverse();
	anis[RDIE]->SetEndEvent(bind(&Enemy::SetIsActive, this));

	anis[LIDLE]->Play();
	anis[RIDLE]->Play();

	curImage = images[LIDLE];
	curAni = anis[LIDLE];
	land = IMAGE->Add(L"Images/landCollision.bmp", 1176, 224);
	gravity = 0.0f;

	rect = new Rect(WIN_WIDTH * 0.8, WIN_HEIGHT * 0.4f, 150, 150);
	hitBox = new Rect();
	hitBox->SetRect(rect->pos.x, rect->pos.y, rect->pos.x + 50, rect->pos.y + 76);
	isDie = false;
	isRight = false;
	isAction = false;

	sword = new Sword();
	attackDelay = 7.0f;
}

Enemy::~Enemy()
{
	delete rect;
	delete hitBox;

	for (Animation* ani : anis)
		delete ani;
}

void Enemy::Update()
{
	if (isActive)
	{
		if (!isDie && !isAction)
		{
			if (!isRight)
			{
				rect->pos.x -= 1.0f;
				pos.x -= 1.0f;
			}
			else
			{
				rect->pos.x += 1.0f;
				pos.x += 1.0f;
			}
		}

		if (rect->Left() > WIN_WIDTH || rect->Right() < 0)
		{
			rect->pos.y = -30;
			isActive = false;
		}

		Idle();
		Attack();
		Die();
		Gravity();
		curAni->Update();
		if (isAction)
		{
			if (!isRight)
			{
				if (curAni->GetFrame().x == 6)
				{
					sword->Play({ rect->pos.x, rect->pos.y - 20 }, (4 * PI) / 5, 3.0f);
				}
			}
			else
			{
				if (curAni->GetFrame().x == 11)
				{
					sword->Play({ rect->pos.x, rect->pos.y - 20 }, PI * 0.25f, 3.0f);
				}
			}
		}
	}
	sword->Update();
	if(!isRight)
		hitBox->SetRect(rect->Left() + 70, rect->Top() + 75, rect->Right() - 40, rect->Bottom());
	else
		hitBox->SetRect(rect->Left() + 50, rect->Top() + 75, rect->Right() - 70, rect->Bottom());
}

void Enemy::Render(HDC hdc)
{
	if(isActive)
		curImage->Render(hdc, *rect, curAni->GetFrame());
	sword->Render(hdc);
	//Rectangle(hdc, hitBox->Left(), hitBox->Top(), hitBox->Right(), hitBox->Bottom());
}

void Enemy::Damage(int damage)
{
	hp -= damage;
}

float Enemy::GetLandY()
{
	if (gravity >= 0)
	{
		return (float)WIN_HEIGHT;
	}
	int x = (int)(pos.x * (land->GetSize().x / (float)WIN_WIDTH * 0.5f));

	for (int i = (int)rect->pos.y; i < WIN_HEIGHT; i++)

	{
		int y = i * land->GetSize().y / WIN_HEIGHT;

		COLORREF color = GetPixel(land->GetMemDC(), x, y);

		if (color != MAGENTA)
			return (float)i;
	}

	return (float)WIN_HEIGHT;
}

void Enemy::Idle()
{
	if (!isDie && !isAction)
	{
		if (!isRight)
		{
			curImage = images[LIDLE];
			curAni = anis[LIDLE];
		}
		else
		{
			curImage = images[RIDLE];
			curAni = anis[RIDLE];
		}
	}
}

void Enemy::Attack()
{
	attackTime += DELTATIME;

	if (attackTime >= attackDelay && !isDie)
	{
		attackTime = 0.0f;
		if (!isAction && curImage != images[LATK] && images[RATK])
		{
			isAction = true;
			if (!isRight)
			{
				curImage = images[LATK];
				curAni = anis[LATK];
			}
			else
			{
				curImage = images[RATK];
				curAni = anis[RATK];
			}
			curAni->Play();
		}
	}
}

void Enemy::Die()
{
	if (!isDie && hp <= 0)
	{		
		score += 100;
		attackTime = 0.0f;
		isDie = true;
		if (isAction)
			isAction = false;

		if (Math::Random(0, 2))
		{
			SOUND->Play("EnemyDie1");
			if (!isRight)
			{
				curImage = images[LDIE1];
				curAni = anis[LDIE1];
			}
			else
			{
				curImage = images[RDIE];
				curAni = anis[RDIE];
			}
		}
		else
		{
			SOUND->Play("EnemyDie2");
			if (!isRight)
			{
				curImage = images[LDIE2];
				curAni = anis[LDIE2];
			}
			else
			{
				curImage = images[RDIE];
				curAni = anis[RDIE];
			}
		}
		
		curAni->Play();
	}
}

void Enemy::Play(Rect rc)
{
	rect->pos.x = Math::Random(50, WIN_WIDTH-50);
	pos = rect->pos;
	pos.x += moveDistance;
	rect->pos.y = 0;
	hitBox->SetRect(rect->Left() + 40, rect->Top() + 40, rect->Right() - 40, rect->Bottom());
	if (rc.pos.x > rect->pos.x)
	{
		curImage = images[RIDLE];
		curAni = anis[RIDLE];
		isRight = true;
	}
	else
	{
		curImage = images[LIDLE];
		curAni = anis[LIDLE];
		isRight = false;
	}
	isActive = true;
	isDie = false;
		
	hp = 2;
	attackTime = 0.0f;
}

void Enemy::Gravity()
{
	gravity -= GRAVITY * DELTATIME;
	rect->pos.y -= gravity;

	if (rect->Bottom() - 20 > GetLandY())
	{
		rect->pos.y = GetLandY() - rect->HalfSize().y + 20;
		gravity = 0.0f;
	}
}

void Enemy::SetAttackDelay()
{
	float val = TIMER->GetWorldTime();

	if (val > 60)
		attackDelay = 3.0f;
	else if (val > 50)
		attackDelay = 4.0f;
	else if (val > 40)
		attackDelay = 5.0f;
	else if (val > 30)
		attackDelay = 5.5f;
	else if (val > 20)
		attackDelay = 6.0f;
	else if (val > 10)
		attackDelay = 6.5f;
}
