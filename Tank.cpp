#include "framework.h"

Tank::Tank()
{
	Load();

	leftAnis[IDLE]->Play();
	SetDir(MOVE);
	
	rect = new Rect(WIN_WIDTH + 600, 275, 150, 150);
	isFire = false;

	attackTime = 0.0f;
	delay = 0.0f;

	for (int i = 0; i < 5; i++)
	{
		bullets.push_back(new TankBullet());
	}

	hp = 20;

	isActive = false;
	isDie = false;

	spawnTime = 0.0f;
	resetTime = 0.0f;
	isRight = false;
}

Tank::~Tank()
{
	for (Animation* ani : leftAnis)
		delete ani;
	delete rect;

	for (Animation* ani : rightAnis)
		delete ani;

	for (TankBullet* tankBullet : bullets)
		delete tankBullet;
}

void Tank::Update()
{
	for (TankBullet* tankBullet : bullets)
		tankBullet->Update();

	if (!isActive && moveDistance > 1175)
	{
		spawnTime += 0.1f;

		if (spawnTime > 15.0f)
			Play();
		return;
	}
	if (isRight)
		Right();
	else
		Left();
	
	curAni->Update();

}

void Tank::Render(HDC hdc)
{
	for (TankBullet* tankBullet : bullets)
		tankBullet->Render(hdc);

	if (!isActive)
		return;

	curImage->Render(hdc, *rect, curAni->GetFrame());

	
}

void Tank::Load()
{
	Image* image = IMAGE->Add(L"Images/Enemy/TankLeft/Tank - Idle.bmp", 200, 100, 2, 1);
	leftImages.push_back(image);
	leftAnis.push_back(new Animation(image));

	image = IMAGE->Add(L"Images/Enemy/TankLeft/Tank - ReadyFire.bmp", 700, 100, 7, 1);
	leftImages.push_back(image);
	leftAnis.push_back(new Animation(image, 0.2f));

	image = IMAGE->Add(L"Images/Enemy/TankLeft/Tank - Fire.bmp", 1200, 100, 12, 1);
	leftImages.push_back(image);
	leftAnis.push_back(new Animation(image));

	image = IMAGE->Add(L"Images/Enemy/TankLeft/Tank - Idle(hit).bmp", 200, 100, 2, 1);
	leftImages.push_back(image);
	leftAnis.push_back(new Animation(image));

	image = IMAGE->Add(L"Images/Enemy/TankLeft/Tank - Move.bmp", 600, 100, 6, 1);
	leftImages.push_back(image);
	leftAnis.push_back(new Animation(image));

	image = IMAGE->Add(L"Images/Enemy/TankLeft/Tank - Destroy.bmp", 600, 100, 6, 1);
	leftImages.push_back(image);
	leftAnis.push_back(new Animation(image));

	leftAnis[IDLE]->SetDefault(true);
	leftAnis[READY]->SetDefault();
	leftAnis[FIRE]->SetDefault();
	leftAnis[FIRE]->SetEndEvent(bind(&Tank::SetIsFire, this));
	leftAnis[HIT]->SetDefault();
	leftAnis[HIT]->SetEndEvent(bind(&Tank::SetIdle, this));
	leftAnis[MOVE]->SetDefault(true);
	leftAnis[DESTROY]->SetDefault();

	image = IMAGE->Add(L"Images/Enemy/TankRight/Tank - Idle.bmp", 200, 100, 2, 1);
	rightImages.push_back(image);
	rightAnis.push_back(new Animation(image));

	image = IMAGE->Add(L"Images/Enemy/TankRight/Tank - ReadyFire.bmp", 700, 100, 7, 1);
	rightImages.push_back(image);
	rightAnis.push_back(new Animation(image, 0.2f));

	image = IMAGE->Add(L"Images/Enemy/TankRight/Tank - Fire.bmp", 1200, 100, 12, 1);
	rightImages.push_back(image);
	rightAnis.push_back(new Animation(image));

	image = IMAGE->Add(L"Images/Enemy/TankRight/Tank - Idle(hit).bmp", 200, 100, 2, 1);
	rightImages.push_back(image);
	rightAnis.push_back(new Animation(image));

	image = IMAGE->Add(L"Images/Enemy/TankRight/Tank - Move.bmp", 600, 100, 6, 1);
	rightImages.push_back(image);
	rightAnis.push_back(new Animation(image));

	image = IMAGE->Add(L"Images/Enemy/TankRight/Tank - Destroy.bmp", 600, 100, 6, 1);
	rightImages.push_back(image);
	rightAnis.push_back(new Animation(image));

	rightAnis[IDLE]->SetDefaultReverse(true);
	rightAnis[READY]->SetDefaultReverse();
	rightAnis[FIRE]->SetDefaultReverse();
	rightAnis[FIRE]->SetEndEvent(bind(&Tank::SetIsFire, this));
	rightAnis[HIT]->SetDefaultReverse();
	rightAnis[HIT]->SetEndEvent(bind(&Tank::SetIdle, this));
	rightAnis[MOVE]->SetDefaultReverse(true);
	rightAnis[DESTROY]->SetDefaultReverse();
}

void Tank::SetDir(TankDirection dir)
{
	if (!isRight)
	{
		switch (dir)
		{
		case Tank::IDLE:
			curImage = leftImages[IDLE];
			curAni = leftAnis[IDLE];
			break;
		case Tank::READY:
			curImage = leftImages[READY];
			curAni = leftAnis[READY];
			break;
		case Tank::FIRE:
			curImage = leftImages[FIRE];
			curAni = leftAnis[FIRE];
			break;
		case Tank::HIT:
			curImage = leftImages[HIT];
			curAni = leftAnis[HIT];
			curAni->Play();
			break;
		case Tank::MOVE:
			curImage = leftImages[MOVE];
			curAni = leftAnis[MOVE];
			if (!curAni->GetIsPlay())
				curAni->Play();
			break;
		case Tank::DESTROY:
			SOUND->Play("Destroy");
			curImage = leftImages[DESTROY];
			curAni = leftAnis[DESTROY];
			if (!curAni->GetIsPlay())
				curAni->Play();
			break;
		default:
			break;
		}
	}
	else
	{
		switch (dir)
		{
		case Tank::IDLE:
			curImage = rightImages[IDLE];
			curAni = rightAnis[IDLE];
			break;
		case Tank::READY:
			curImage = rightImages[READY];
			curAni = rightAnis[READY];
			break;
		case Tank::FIRE:
			curImage = rightImages[FIRE];
			curAni = rightAnis[FIRE];
			break;
		case Tank::HIT:
			curImage = rightImages[HIT];
			curAni = rightAnis[HIT];
			curAni->Play();
			break;
		case Tank::MOVE:
			curImage = rightImages[MOVE];
			curAni = rightAnis[MOVE];
			if (!curAni->GetIsPlay())
				curAni->Play();
			break;
		case Tank::DESTROY:
			SOUND->Play("Destroy");
			curImage = rightImages[DESTROY];
			curAni = rightAnis[DESTROY];
			if (!curAni->GetIsPlay())
				curAni->Play();
			break;
		default:
			break;
		}

	}
}

void Tank::Fire()
{
	SetDir(FIRE);
	curAni->Play();
}

void Tank::SetIdle()
{
	SetDir(IDLE);
}

void Tank::Damage(int damage)
{
	if (curImage != leftImages[MOVE] && !isDie && curImage != rightImages[MOVE])
	{
		hp -= damage;
		SetDir(HIT);
		isFire = false;
		attackTime = 0.0f;
	}
}

void Tank::Play()
{
	if (Math::Random(0, 2))
	{
		isRight = false;
		rect->pos.x = WIN_WIDTH + 200;
		rect->pos.y = 275;
		SetDir(MOVE);
		hp = 20;
		SOUND->Play("TankMove");
		isActive = true;
		isDie = false;
		spawnTime = 0.0f;
	}
	else
	{
		isRight = true;
		rect->pos.x = -200;
		rect->pos.y = 275;
		SetDir(MOVE);
		hp = 20;
		SOUND->Play("TankMove");
		isActive = true;
		isDie = false;
		spawnTime = 0.0f;
	}
}

void Tank::Left()
{
	if (curImage == leftImages[MOVE] && isActive)
	{
		rect->pos.x -= 1.0f;
	}

	if (isActive)
	{
		if (!isDie)
		{
			if (rect->pos.x < 1000 && curImage == leftImages[MOVE])
			{
				SOUND->Stop("TankMove");
				SetDir(IDLE);
			}
			if (curImage == leftImages[IDLE])
				attackTime += 0.1f;

			if (attackTime > 10.0f && !isFire)
			{
				SOUND->Play("TankFireReady");
				attackTime = 0.0f;
				isFire = true;
				SetDir(READY);
				curAni->Play();
			}
			if (!isFire && curImage != leftImages[HIT] && curImage != leftImages[MOVE])
			{
				SetDir(IDLE);
			}

			if (curImage == leftImages[READY])
			{
				if (!curAni->GetIsPlay())
				{
					delay += 0.01f;
				}
			}

			if (delay > 1.0f)
			{
				SOUND->Play("TankFire");
				EFFECT->Start("TankFire", { rect->pos.x - 90, rect->pos.y });
				for (TankBullet* tankBullet : bullets)
				{
					if (!tankBullet->GetIsActive())
					{
						tankBullet->Fire({ rect->pos.x - 90, rect->pos.y + 5 }, isRight);
						break;
					}
				}
				delay = 0.0f;
				SetDir(FIRE);
				curAni->Play();
			}

			if (hp <= 0 && !isDie)
			{
				SOUND->Stop("TankMove");
				if (isActive)
					score += 500;
				isDie = true;
				SetDir(DESTROY);
			}
		}
		else
		{
			if (curAni == leftAnis[DESTROY])
			{
				if (curAni->GetFrame().x == 5)
				{
					resetTime += 0.1f;
					if (resetTime > 5.0f)
					{
						resetTime = 0.0f;
						isActive = false;
					}
				}
			}
		}
	}
}

void Tank::Right()
{
	if (curImage == rightImages[MOVE] && isActive)
	{
		rect->pos.x += 1.0f;
	}

	if (isActive)
	{
		if (!isDie)
		{
			if (rect->pos.x > 100 && curImage == rightImages[MOVE])
			{
				SOUND->Stop("TankMove");
				SetDir(IDLE);
			}
			if (curImage == rightImages[IDLE])
				attackTime += 0.1f;

			if (attackTime > 10.0f && !isFire)
			{
				SOUND->Play("TankFireReady");
				attackTime = 0.0f;
				isFire = true;
				SetDir(READY);
				curAni->Play();
			}
			if (!isFire && curImage != rightImages[HIT] && curImage != rightImages[MOVE])
			{
				SetDir(IDLE);
			}

			if (curImage == rightImages[READY])
			{
				if (!curAni->GetIsPlay())
				{
					delay += 0.01f;
				}
			}

			if (delay > 1.0f)
			{
				SOUND->Play("TankFire");
				EFFECT->Start("TankFire", { rect->pos.x + 90, rect->pos.y });
				for (TankBullet* tankBullet : bullets)
				{
					if (!tankBullet->GetIsActive())
					{
						tankBullet->Fire({ rect->pos.x + 90, rect->pos.y + 5 }, isRight);
						break;
					}
				}
				delay = 0.0f;
				SetDir(FIRE);
				curAni->Play();
			}

			if (hp <= 0 && !isDie)
			{
				SOUND->Stop("TankMove");
				if (isActive)
					score += 500;
				isDie = true;
				SetDir(DESTROY);
			}
		}
		else
		{
			if (curAni == rightAnis[DESTROY])
			{
				if (curAni->GetFrame().x == 0)
				{
					resetTime += 0.1f;
					if (resetTime > 5.0f)
					{
						resetTime = 0.0f;
						isActive = false;
					}
				}
			}
		}
	}
}
