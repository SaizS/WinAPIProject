#include "framework.h"

Npc::Npc()
{
	Image* image = IMAGE->Add(L"Images/Npc/Npc - Idle.bmp", 300, 60, 5, 1);
	images.push_back(image);
	anis.push_back(new Animation(image, 0.08f));

	image = IMAGE->Add(L"Images/Npc/Npc - Up.bmp", 240, 60, 4, 1);
	images.push_back(image);
	anis.push_back(new Animation(image, 0.08f));

	image = IMAGE->Add(L"Images/Npc/Npc - RightWorking.bmp", 720, 60, 12, 1);
	images.push_back(image);
	anis.push_back(new Animation(image, 0.08f));

	image = IMAGE->Add(L"Images/Npc/Npc - LeftWorking.bmp", 720, 60, 12, 1);
	images.push_back(image);
	anis.push_back(new Animation(image, 0.08f));

	image = IMAGE->Add(L"Images/Npc/Npc - Give.bmp", 660, 60, 11, 1);
	images.push_back(image);
	anis.push_back(new Animation(image, 0.08f));

	image = IMAGE->Add(L"Images/Npc/Npc - Bye.bmp", 840, 60, 14, 1);
	images.push_back(image);
	anis.push_back(new Animation(image, 0.08f));

	image = IMAGE->Add(L"Images/Npc/Npc - Run.bmp", 480, 60, 8, 1);
	images.push_back(image);
	anis.push_back(new Animation(image, 0.05f));

	anis[IDLE]->SetDefault(true, true);
	anis[UP]->SetDefault();
	anis[RWORKING]->SetDefaultReverse(true);
	anis[LWORKING]->SetDefault(true);
	anis[GIVE]->SetDefault();
	anis[BYE]->SetDefault();
	anis[RUN]->SetDefault(true);

	anis[UP]->SetEndEvent(bind(&Npc::SetLWorking, this));
	anis[GIVE]->SetEndEvent(bind(&Npc::SetBye, this));
	anis[BYE]->SetEndEvent(bind(&Npc::SetRun, this));

	SetDir(IDLE);
	rect = new Rect(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f, 100, 100);
	isActive = false;
	turnTime = 0.0f;

	frameItem = new FrameItem();
	bombItem = new BombItem();
}

Npc::~Npc()
{
	for (Animation* ani : anis)
		delete ani;
	delete rect;
	delete frameItem;
	delete bombItem;
}

void Npc::Update()
{
	if (!isActive)
	{
		if (moveDistance > 1175)
			spawnTime += 0.1f;
		if (spawnTime > 10.0f)
			Spawn();
		return;
	}


	rect->pos.y += 7.0f;

	if (rect->pos.y > WIN_HEIGHT - 150)
	{
		rect->pos.y = WIN_HEIGHT - 150;
	}

	curAni->Update();

	if (curAni == anis[IDLE])
	{
		for (Bullet* bullet : player->GetBullet())
		{
			if (bullet->GetIsActive())
			{
				float minX = min(bullet->GetRect().Right(), rect->Right());
				float maxX = max(bullet->GetRect().Left(), rect->Left());

				float minY = min(bullet->GetRect().Bottom(), rect->Bottom());
				float maxY = max(bullet->GetRect().Top(), rect->Top());

				Vector pos;
				pos.x = minX - maxX;
				pos.y = minY - maxY;

				if (pos.x > 0 && pos.y > 0)
				{
					SetDir(UP);
					break;
				}				
			}
		}

		if (player->GetFrame()->GetIsActive())
		{
			float minX = min(player->GetFrame()->GetRect().Right(), rect->Right());
			float maxX = max(player->GetFrame()->GetRect().Left(), rect->Left());

			float minY = min(player->GetFrame()->GetRect().Bottom(), rect->Bottom());
			float maxY = max(player->GetFrame()->GetRect().Top(), rect->Top());

			Vector pos;
			pos.x = minX - maxX;
			pos.y = minY - maxY;

			if (pos.x > 0 && pos.y > 0)
			{
				SetDir(UP);
			}
		}
	}

	if (curAni == anis[LWORKING])
	{
		turnTime += 0.1f;
		rect->pos.x -= 1.0f;
	}
	if (curAni == anis[RWORKING])
	{
		turnTime += 0.1f;
		rect->pos.x += 1.0f;
	}

	if (turnTime > 10.0f)
	{
		turnTime = 0.0f;
		if (curAni == anis[LWORKING])
			SetDir(RWORKING);
		else
			SetDir(LWORKING);
	}

	if (curAni == anis[RUN])
	{
		rect->pos.x -= 4.0f;
		if (rect->Right() < 0)
			isActive = false;
	}

	Give();

	if (frameItem->Eat(player->GetRect()))
	{
		player->SetFrameBulletCount(20);
	}

	if (bombItem->Eat(player->GetRect()))
	{
		player->SetBombCount(10);
	}
	bombItem->Update();
}

void Npc::Render(HDC hdc)
{
	if (!isActive)
		return;
	curImage->Render(hdc, *rect, curAni->GetFrame());
	frameItem->Render(hdc);
	bombItem->Render(hdc);
}

void Npc::SetDir(NpcDirection dir)
{
	curImage = images[dir];
	curAni = anis[dir];
	curAni->Play();
}

void Npc::SetBye()
{
	SOUND->Play("Npc - Bye");

	if (Math::Random(0, 2))
	{
		frameItem->SetIsActiveTrue({ rect->pos.x - 25, rect->Bottom() - 18 });
	}
	else
	{
		bombItem->SetIsActiveTrue({ rect->pos.x - 25, rect->Bottom() - 18 });
	}
	SetDir(BYE);
}

void Npc::Give()
{
	if (curAni == anis[RWORKING] || curAni == anis[LWORKING])
	{
		Rect rc = player->GetRect();

		float minX = min(rc.Right(), rect->Right());
		float maxX = max(rc.Left(), rect->Left());

		float minY = min(rc.Bottom(), rect->Bottom());
		float maxY = max(rc.Top(), rect->Top());

		Vector pos;
		pos.x = minX - maxX;
		pos.y = minY - maxY;

		if (pos.x > 0 && pos.y > 0)
		{
			SOUND->Play("Npc - Give");
			SetDir(GIVE);
		}
	}
}

void Npc::Spawn()
{
	rect->pos.x = Math::Random(100, WIN_WIDTH - 100);
	rect->pos.y = -200;
	isActive = true;
	SetDir(IDLE);
}
