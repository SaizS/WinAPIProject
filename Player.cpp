#include "framework.h"

Player::Player()
	: jumpPower(0.0f), gravity(0.0f), isRight(true), isMove(false), isJump(false), isAction(false), isDie(false), isUp(false), isItem(false)
{
	InitUpperMotion();
	InitLowerMotion();

	playerRect = new Rect(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f, 130.0f, 130.0f);
	hitBox = new Rect(0, 0, 0, 0);

	body[0] = new Image(*lowerBody[RIDLE]);
	body[1] = new Image(*upperBody[RIDLE]);	

	bodyAni[0] = new Animation(body[0], 0.05f);
	bodyAni[1] = new Animation(body[1], 0.05f);

	SetUp(ITEMRIDLE);
	SetDown(RIDLE);

	for (int i = 0; i < BULLETCOUNT; i++)
	{
		bullets.push_back(new Bullet());
		itemBullets.push_back(new ItemBullet());
	}

	damage = 1;

	pos = { playerRect->pos.x, playerRect->pos.y };

	for (int i = 0; i < BOMBCOUNT; i++)
		bombs.push_back(new Bomb());

	frameBullet = new FrameBullet();
	life = 2;
	frameBulletCount = 0;
	bombCount = 10;
}

Player::~Player()
{
	for (Animation* ani : upperAni)
		delete ani;
	for (Animation* ani : lowerAni)
		delete ani;
	for (Bullet* bullet : bullets)
		delete bullet;
	for (ItemBullet* item : itemBullets)
		delete item;
	for (Bomb* bomb : bombs)
		delete bomb;

	delete playerRect;	
	delete frameBullet;
}

void Player::Update()
{
	bool check = false;
	for (Bullet* bullet : bullets)
		bullet->Update();

	for (ItemBullet* item : itemBullets)		
		item->Update();	
	
	for (Bomb* bomb : bombs)
		bomb->Update();

	bodyAni[0]->Update();
	bodyAni[1]->Update();

	if (!isDie)
	{
		Move();
		Jump();
		Attack();
		BulletCollision();
		BombCollision();
		Map();
	}

	if (frameBulletCount > 0)
		isItem = true;
	else
		isItem = false;

	SetDie();

	frameBullet->Update();

	hitBox->SetRect(playerRect->pos.x - 18, playerRect->pos.y - 25, playerRect->pos.x + 18, playerRect->pos.y + 40);
}

void Player::Render(HDC hdc)
{
	for (Bullet* bullet : bullets)
		bullet->Render(hdc);

	for (Bomb* bomb : bombs)
		bomb->Render(hdc);	

	for (ItemBullet* item : itemBullets)
		item->Render(hdc);

	if (!isDie)
	{
		if (body[1] != upperBody[RDOWN] && body[1] != upperBody[RDOWNIDLE] && body[1] != upperBody[RDOWNMOVE] &&
			body[1] != upperBody[LDOWN] && body[1] != upperBody[LDOWNIDLE] && body[1] != upperBody[LDOWNMOVE] &&
			body[1] != upperBody[RDOWNFIRE] && body[1] != upperBody[LDOWNFIRE]&&
			body[1] != upperBody[ITEMRDOWNIDLE] && body[1] != upperBody[ITEMRDOWNMOVE] &&
			body[1] != upperBody[ITEMLDOWNIDLE] && body[1] != upperBody[ITEMLDOWNMOVE] &&
			body[1] != upperBody[ITEMRDOWNFIRE] && body[1] != upperBody[ITEMLDOWNFIRE] &&
			body[1] != upperBody[RDOWNBOMB] && body[1] != upperBody[LDOWNBOMB] &&
			body[1] != upperBody[ITEMRDOWNATK] && body[1] != upperBody[ITEMLDOWNATK] &&
			body[1] != upperBody[ITEMRDOWNBOMB] && body[1] != upperBody[ITEMLDOWNBOMB])
				body[0]->Render(hdc, *playerRect, bodyAni[0]->GetFrame());

		if (body[1] == upperBody[ITEMRUPFIRE] || body[1] == upperBody[ITEMLUPFIRE])
		{
			body[1]->Render(hdc, { playerRect->pos.x, playerRect->pos.y - 60, playerRect->size.x, playerRect->size.y }, bodyAni[1]->GetFrame());
		}
		else
		{
			body[1]->Render(hdc, *playerRect, bodyAni[1]->GetFrame());
		}		
	}
	else
	{
		if(resetTime % 2 == 0)
			body[1]->Render(hdc, *playerRect, bodyAni[1]->GetFrame());
	}
	
	frameBullet->Render(hdc);
	//Rectangle(hdc, hitBox->Left(), hitBox->Top(), hitBox->Right(), hitBox->Bottom());
}

void Player::Move()
{
	if (KEYBOARD->KeyPress(VK_UP))
	{
		if (!isItem)
		{
			if (!isUp && !isAction)
			{
				if (isRight)
					SetUp(RUP);
				else
					SetUp(LUP);
			}
			if (isUp && !isAction)
			{
				if (isRight)
					SetUp(RUPIDLE);
				else
					SetUp(LUPIDLE);
			}
		}
		else
		{
			isUp = true;
			if (!isAction)
			{
				if (isRight)
					SetUp(ITEMRUP);
				else
					SetUp(ITEMLUP);
			}
		}
	}
	else
		isUp = false;
	//좌우 키가 눌렸을 경우
	if (KEYBOARD->KeyPress(VK_RIGHT) || KEYBOARD->KeyPress(VK_LEFT) || KEYBOARD->KeyPress(VK_DOWN))
	{
		isMove = true;
		if (KEYBOARD->KeyPress(VK_RIGHT) && !isDown)
		{
			if (!isRight && !isDown && !isItem)
			{
				SetUp(RRUN);
				isAction = false;
			}
			if (!isRight && !isDown && isItem)
			{
				SetUp(ITEMRRUN);
				isAction = false;
			}
			if (!isDown)
			{
				isRight = true;
				playerRect->pos.x += PLAYERSPEED;
				pos.x += PLAYERSPEED;
				if (!isAction &&!KEYBOARD->KeyPress(VK_UP))
				{
					if (!isItem)
						SetUp(RRUN);
					else
						SetUp(ITEMRRUN);
				}
				if (!isJump)
				{
					SetDown(RRUN);
				}
				else
				{
					SetDown(RJUMP);
				}
			}
		}
		if(KEYBOARD->KeyPress(VK_LEFT) && !isDown)
		{
			if (isRight && !isDown && !isItem)
			{
				SetUp(LRUN);
				isAction = false;
			}
			if (isRight && !isDown && isItem)
			{
				SetUp(ITEMLRUN);
				isAction = false;
			}
			if (!isDown)
			{
				isRight = false;
				playerRect->pos.x -= PLAYERSPEED;
				pos.x -= PLAYERSPEED;

				if (!isAction && !KEYBOARD->KeyPress(VK_UP))
				{
					if (!isItem)
						SetUp(LRUN);
					else
						SetUp(ITEMLRUN);
				}
				if (!isJump)
				{
					SetDown(LRUN);
				}
				else
				{
					SetDown(LJUMP);
				}
			}
		}
		if (KEYBOARD->KeyPress(VK_DOWN))
		{
			isDown = true;
			if(KEYBOARD->KeyPress(VK_RIGHT) || KEYBOARD->KeyPress(VK_LEFT))
			{
				if (KEYBOARD->KeyPress(VK_RIGHT) && !isAction)
				{
					isRight = true;

					if (!isItem)
						SetUp(RDOWNMOVE);
					else
						SetUp(ITEMRDOWNMOVE);
					playerRect->pos.x += PLAYERSPEED - 2.0f;
					pos.x += PLAYERSPEED - 2.0f;
				}
				if(KEYBOARD->KeyPress(VK_LEFT) && !isAction)
				{
					isRight = false;
					if (!isItem)
						SetUp(LDOWNMOVE);
					else
						SetUp(ITEMLDOWNMOVE);
					playerRect->pos.x -= PLAYERSPEED - 2.0f;
					pos.x -= PLAYERSPEED - 2.0f;
				}
			}
			else
			{
				if (!isAction)
				{
					if (!isItem)
					{
						if (!isDown)
						{
							if (isRight)
								SetUp(RDOWN);
							else
								SetUp(LDOWN);
						}
						else
						{
							if (isRight)
								SetUp(RDOWNIDLE);
							else
								SetUp(LDOWNIDLE);
						}
					}
					else
					{
						if (isRight)
							SetUp(ITEMRDOWNIDLE);
						else
							SetUp(ITEMLDOWNIDLE);
					}
				}
			}
		}
	}
	//좌우 키가 눌리지 않았을 경우
	else
	{
		isMove = false;
		isDown = false;
		if (isRight)
		{
			SetDown(RIDLE);
			if (!isAction && !KEYBOARD->KeyPress(VK_UP))
			{
				if (!isItem)
					SetUp(RIDLE);
				else
					SetUp(ITEMRIDLE);
			}
		}
		else
		{
			SetDown(LIDLE);
			if (!isAction && !KEYBOARD->KeyPress(VK_UP))
			{
				SetDown(LIDLE);
				if (!isItem)
					SetUp(LIDLE);
				else
					SetUp(ITEMLIDLE);
			}
		}
	}
}

void Player::Jump()
{
	if (!isJump && KEYBOARD->KeyDown('S'))
	{
		isAction = false;
		isJump = true;
		jumpPower = JUMPPOWER;

		if (isRight)
		{
			SetUp(RJUMP);
			SetDown(RJUMP);
		}
		else
		{
			SetUp(LJUMP);
			SetDown(RJUMP);
		}
	}

	gravity += GRAVITY * DELTATIME;
	jumpPower -= gravity;
	playerRect->pos.y -= jumpPower;	
	pos.y = playerRect->pos.y;

	if (playerRect->Bottom()-30 > GetLandY() && playerRect->pos.y > 0)
	{
		playerRect->pos.y = GetLandY() - playerRect->HalfSize().y + 30;
		gravity = 0.0f;
		jumpPower = 0.0f;

		if (isJump)
		{
			isJump = false;
		}
	}
}

void Player::Attack()
{
	if (KEYBOARD->KeyDown('A'))
	{
		bool check = false;
		for (Enemy* enemy : em->GetEnemy())
		{
			if (enemy->GetIsActive() && !enemy->GetIsDie())
			{
				Rect box = enemy->GetHitBox();

				float minX = min(hitBox->Right(), box.Right());
				float maxX = max(hitBox->Left(), box.Left());

				float minY = min(hitBox->Bottom(), box.Bottom());
				float maxY = max(hitBox->Top(), box.Top());

				Vector pos;
				pos.x = minX - maxX;
				pos.y = minY - maxY;

				if (pos.x > 0 && pos.y > 0)
				{
					SOUND->Play("attack");
					isAction = true;
					if (!isDown)
					{
						if (isRight)
							SetUp(RATK);
						else
							SetUp(LATK);
					}
					else
					{
						if (!isItem)
						{
							if (isRight)
								SetUp(RDOWNATK);
							else
								SetUp(LDOWNATK);
						}
						else
						{
							if (isRight)
								SetUp(ITEMRDOWNATK);
							else
								SetUp(ITEMLDOWNATK);
						}
					}
					enemy->Damage(3);
					check = true;
					break;
				}					
			}
		}
		if (!check)
		{
			isAction = true;
			
			if (!isUp && !isDown)
			{

				if (!isItem)
				{
					if (isRight)
						SetUp(RFIRE);
					else
						SetUp(LFIRE);
				}
				else
				{
					if (!frameBullet->GetIsActive())
					{			
						if (isRight)
							SetUp(ITEMRFIRE);
						else
							SetUp(ITEMLFIRE);
					}
				}
			}
			else if (isDown)
			{
				if (!isItem)
				{
					if (isRight)
						SetUp(RDOWNFIRE);
					else
						SetUp(LDOWNFIRE);
				}
				else
				{
					if (!frameBullet->GetIsActive())
					{
						if (isRight)
							SetUp(ITEMRDOWNFIRE);
						else
							SetUp(ITEMLDOWNFIRE);
					}
				}
			}
			else
			{
				if (!isItem)
				{
					if (isRight)
						SetUp(RUPFIRE);
					else
						SetUp(LUPFIRE);
				}
				else
				{
					if (isRight)
						SetUp(ITEMRUPFIRE);
					else
						SetUp(ITEMLUPFIRE);
				}
			}
			if (!isItem)
			{
				SOUND->Play("basic", 0.5f);
				for (Bullet* bullet : bullets)
				{
					if (!bullet->GetIsActive())
					{
						if (!isUp && !isDown)
						{
							if (isRight)
							{
								bullet->Fire({ playerRect->pos.x + 60, playerRect->pos.y - 18 }, isRight, isUp);
							}
							else
							{
								bullet->Fire({ playerRect->pos.x - 60, playerRect->pos.y - 18 }, isRight, isUp);
							}
						}
						else if (isDown)
						{
							if (isRight)
							{
								bullet->Fire({ playerRect->pos.x + 60, playerRect->pos.y + 10 }, isRight, isUp);
							}
							else
							{
								bullet->Fire({ playerRect->pos.x - 60, playerRect->pos.y + 10 }, isRight, isUp);
							}
						}
						else
						{
							bullet->Fire({ playerRect->pos.x, playerRect->pos.y - 80 }, isRight, isUp);
						}
						break;
					}
				}
				bodyAni[1]->Play();
			}
			else
			{
				if (!frameBullet->GetIsActive())
				{
					frameBulletCount--;
					SOUND->Play("frame", 0.5f);
					if (!isUp)
					{
						if (isRight)
							frameBullet->Fire({ playerRect->pos.x + 150, playerRect->pos.y }, isRight, isUp);
						else
							frameBullet->Fire({ playerRect->pos.x - 150, playerRect->pos.y }, isRight, isUp);
					}
					else
					{
						frameBullet->Fire({ playerRect->pos.x, playerRect->pos.y - 150 }, isRight, isUp);
					}
				}
			}
		}
	}
	if (KEYBOARD->KeyDown('D') && bombCount > 0)
	{
		bombCount -= 1;
		isAction = true;
		if (isRight)
		{
			for (Bomb* bomb : bombs)
			{
				if (!bomb->GetIsActive())
				{
					bomb->PlayBomb(PI * 0.25f, playerRect->pos, pos);
					break;
				}
			}
			if (!isDown)
			{
				if (!isItem)
					SetUp(RBOMB);
				else
					SetUp(ITEMRBOMB);
			}
			else
			{
				if (!isItem)
					SetUp(RDOWNBOMB);
				else
					SetUp(ITEMRDOWNBOMB);
			}
		}
		else
		{
			for (Bomb* bomb : bombs)
			{
				if (!bomb->GetIsActive())
				{
					bomb->PlayBomb(2.35f, playerRect->pos, pos);
					break;
				}
			}
			if (!isDown)
			{
				if (!isItem)
					SetUp(LBOMB);
				else
					SetUp(ITEMLBOMB);
			}
			else
			{
				if (!isItem)
					SetUp(LDOWNBOMB);
				else
					SetUp(ITEMLDOWNBOMB);
			}
		}
	}
	if (KEYBOARD->KeyDown('F'))
	{
		if (frameBulletCount > 0)
		{
			if (isItem)
				isItem = false;
			else
				isItem = true;
		}
	}
}

void Player::Map()
{
	if (playerRect->pos.x > 800 && bg->GetRect().Right() > WIN_WIDTH)
	{
		float val = playerRect->pos.x - 800;
		bg->MoveMap(PLAYERSPEED);
		for(Enemy* enemy : em->GetEnemy())
			enemy->Move(PLAYERSPEED);
		moveDistance += PLAYERSPEED;
		playerRect->pos.x = 800;
		//pos.x -= 0.001;
	}
}

void Player::SetUp(Direction dir)
{
	body[1] = upperBody[dir];
	bodyAni[1] = upperAni[dir];

	if (!bodyAni[1]->GetIsPlay())
		bodyAni[1]->Play();
}

void Player::SetDown(Direction dir)
{
	body[0] = lowerBody[dir];
	bodyAni[0] = lowerAni[dir];

	if (!bodyAni[0]->GetIsPlay())
		bodyAni[0]->Play();
}

void Player::BulletCollision()
{
	for (Enemy* enemy : em->GetEnemy())
	{
		if (enemy->GetIsActive() && !enemy->GetIsDie())
		{
			Rect rc;
			Rect box = enemy->GetHitBox();
			Bullet* temp = NULL;
			for (Bullet* bullet : bullets)
			{
				if (bullet->GetIsActive())
				{
					rc = bullet->GetRect();
					temp = bullet;

					float minX = min(rc.Right(), box.Right());
					float maxX = max(rc.Left(), box.Left());

					float minY = min(rc.Bottom(), box.Bottom());
					float maxY = max(rc.Top(), box.Top());

					Vector pos;
					pos.x = minX - maxX;
					pos.y = minY - maxY;

					if (pos.x > 0 && pos.y > 0)
					{
						enemy->Damage(damage);
						temp->SetIsActive();
						SOUND->Play("hit");
					}
				}
			}			
		}
	}

	if (frameBullet->GetIsActive())
	{
		for (Enemy* enemy : em->GetEnemy())
		{
			if (!enemy->GetIsDie())
			{
				Rect rc = frameBullet->GetRect();
				Rect box = enemy->GetHitBox();

				float minX = min(rc.Right(), box.Right());
				float maxX = max(rc.Left(), box.Left());

				float minY = min(rc.Bottom(), box.Bottom());
				float maxY = max(rc.Top(), box.Top());

				Vector pos;
				pos.x = minX - maxX;
				pos.y = minY - maxY;

				if (pos.x > 0 && pos.y > 0)
				{
					enemy->Damage(3);
				}
			}
		}
	}


	for (Bullet* bullet : bullets)
	{
		if (bullet->GetIsActive())
		{
			Rect rc;
			Rect box = em->GetTank()->GetRect();
			box.size.x = 100;

			rc = bullet->GetRect();

			float minX = min(rc.Right(), box.Right());
			float maxX = max(rc.Left(), box.Left());

			float minY = min(rc.Bottom(), box.Bottom());
			float maxY = max(rc.Top(), box.Top());

			Vector pos;
			pos.x = minX - maxX;
			pos.y = minY - maxY;

			if (pos.x > 0 && pos.y > 0 && em->GetTank()->GetIsActive())
			{
				em->GetTank()->Damage(1);
				bullet->SetIsActive();
				SOUND->Play("hit");
			}
		}
	}

	if (frameBullet->GetIsActive())
	{
		Rect rc = frameBullet->GetRect();
		Rect box = em->GetTank()->GetRect();
		box.size.x = 100;

		float minX = min(rc.Right(), box.Right());
		float maxX = max(rc.Left(), box.Left());

		float minY = min(rc.Bottom(), box.Bottom());
		float maxY = max(rc.Top(), box.Top());

		Vector pos;
		pos.x = minX - maxX;
		pos.y = minY - maxY;

		if (pos.x > 0 && pos.y > 0 && em->GetTank()->GetIsActive())
		{
			if (isRight)
			{
				if (frameBullet->GetFrame() == 1)
				{
					em->GetTank()->Damage(3);
				}
			}
			else
			{
				if (frameBullet->GetFrame() == 11)
				{
					em->GetTank()->Damage(3);
				}
			}
		}
	}	
}

void Player::BombCollision()
{
	for (Enemy* enemy : em->GetEnemy())
	{
		if (enemy->GetIsActive() && !enemy->GetIsDie())
		{
			Rect rc;
			Rect box = enemy->GetHitBox();
			Bomb* temp = NULL;
			for (Bomb* bomb : bombs)
			{
				if (bomb->GetIsActive())
				{
					rc = bomb->GetRect();
					temp = bomb;
					break;
				}
			}

			float minX = min(rc.Right(), box.Right());
			float maxX = max(rc.Left(), box.Left());

			float minY = min(rc.Bottom(), box.Bottom());
			float maxY = max(rc.Top(), box.Top());

			Vector pos;
			pos.x = minX - maxX;
			pos.y = minY - maxY;

			if (pos.x > 0 && pos.y > 0)
			{
				enemy->Damage(3);
				temp->SetIsActive();
				EFFECT->Start("bomb", { temp->GetRect().pos.x, temp->GetRect().pos.y - 50 });
				SOUND->Play("bomb");
				break;				
			}
			
		}
	}

	Rect rc;
	Rect box = em->GetTank()->GetRect();
	box.pos.y += 100;
	for (Bomb* bomb : bombs)
	{
		if (bomb->GetIsActive())
		{
			rc = bomb->GetRect();
			float minX = min(rc.Right(), box.Right());
			float maxX = max(rc.Left(), box.Left());

			float minY = min(rc.Bottom(), box.Bottom());
			float maxY = max(rc.Top(), box.Top());

			Vector pos;
			pos.x = minX - maxX;
			pos.y = minY - maxY;

			if (pos.x > 0 && pos.y > 0)
			{
				em->GetTank()->Damage(4);
				bomb->SetIsActive();
				EFFECT->Start("bomb", { bomb->GetRect().pos.x, bomb->GetRect().pos.y - 50 });
				SOUND->Play("bomb");
			}
		}
	}
}

float Player::GetLandY()
{
	if (jumpPower > 0)
	{
		return (float)WIN_HEIGHT;
	}

	int x = (int)(pos.x * (land->GetSize().x / (float)WIN_WIDTH * 0.5f));

	for (int i = (int)playerRect->pos.y; i < WIN_HEIGHT; i++)
	{
		int y = i * land->GetSize().y / WIN_HEIGHT;

		COLORREF color = GetPixel(land->GetMemDC(), x, y);

		if (color != MAGENTA)
			return (float)i;
	}

	return (float)WIN_HEIGHT;
}

void Player::InitUpperMotion()
{
	Image* image = IMAGE->Add(L"Images/UpperBody - RightIdle.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.05f));

	image = IMAGE->Add(L"Images/UpperBody - RightRunIdle.bmp", 1800, 64, 18, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.05f));

	image = IMAGE->Add(L"Images/UpperBody - LeftIdle.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.05f));

	image = IMAGE->Add(L"Images/UpperBody - LeftRunIdle.bmp", 1800, 64, 18, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.05f));

	image = IMAGE->Add(L"Images/UpperBody - RightJump.bmp", 600, 100, 6, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.08f));

	image = IMAGE->Add(L"Images/UpperBody - LeftJump.bmp", 600, 100, 6, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.08f));

	image = IMAGE->Add(L"Images/UppperBody - RightFire.bmp", 1000, 64, 10, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.03f));

	image = IMAGE->Add(L"Images/UppperBody - LeftFire.bmp", 1000, 64, 10, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.03f));

	image = IMAGE->Add(L"Images/UpperBody - RightBomb.bmp", 600, 64, 6, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.05f));

	image = IMAGE->Add(L"Images/UpperBody - LeftBomb.bmp", 600, 64, 6, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.05f));

	image = IMAGE->Add(L"Images/UpperBody - RightAttack.bmp", 600, 64, 6, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/UpperBody - LeftAttack.bmp", 600, 64, 6, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/PlayerDie.bmp", 2100, 64, 21, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/UpperBody - RightUp.bmp", 200, 64, 2, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/UpperBody - RightUpIdle.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/UpperBody - LeftUp.bmp", 200, 64, 2, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/UpperBody - LeftUpIdle.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/UpperBody - RightUpFire.bmp", 1000, 64, 10, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/UpperBody - LeftUpFire.bmp", 1000, 64, 10, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/PlayerRightSit.bmp", 300, 64, 3, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/PlayerRightSitIdle.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/PlayerRightSitMove.bmp", 1100, 64, 11, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/PlayerLeftSit.bmp", 300, 64, 3, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/PlayerLeftSitIdle.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/PlayerLeftSitMove.bmp", 1100, 64, 11, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/PlayerRightSitFire.bmp", 1400, 64, 14, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/PlayerLeftSitFire.bmp", 1400, 64, 14, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/PlayerRightSitAttack.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/PlayerLeftSitAttack.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/PlayerRightSitBomb.bmp", 600, 64, 6, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/PlayerLeftSitBomb.bmp", 600, 64, 6, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemRightIdle.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemRightRunIdle.bmp", 1200, 64, 12, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemRightFire.bmp", 500, 64, 5, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemLeftIdle.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemLeftRunIdle.bmp", 1200, 64, 12, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemLeftFire.bmp", 500, 64, 5, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemRightUpIdle.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemLeftUpIdle.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemRightUpFire2.bmp", 600, 64, 6, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemLeftUpFire.bmp", 600, 64, 6, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemRightBomb.bmp", 600, 64, 6, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemLeftBomb.bmp", 600, 64, 6, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemRightSitIdle.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemRightSitMove.bmp", 1100, 64, 11, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemRightSitFire.bmp", 800, 64, 8, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemLeftSitIdle.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemLeftSitMove.bmp", 1100, 64, 11, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemLeftSitFire.bmp", 800, 64, 8, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemRightSitAttack.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemLeftSitAttack.bmp", 400, 64, 4, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemRightSitBomb.bmp", 600, 64, 6, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));

	image = IMAGE->Add(L"Images/ItemBody/UpperBody - ItemLeftSitBomb.bmp", 600, 64, 6, 1);
	upperBody.push_back(image);
	upperAni.push_back(new Animation(image, 0.04f));


	upperAni[RIDLE]->SetDefault(true);
	upperAni[RIDLE]->Play();
	upperAni[RRUN]->SetDefault(true);
	upperAni[RRUN]->Play();
	upperAni[RFIRE]->SetDefault();
	upperAni[RJUMP]->SetDefault(false, true);
	upperAni[LJUMP]->SetDefaultReverse(false, true);
	upperAni[LIDLE]->SetDefaultReverse(true);
	upperAni[LIDLE]->Play();
	upperAni[LRUN]->SetDefaultReverse(true);
	upperAni[LRUN]->Play();
	upperAni[LFIRE]->SetDefaultReverse();
	upperAni[RBOMB]->SetDefault(false);
	upperAni[LBOMB]->SetDefaultReverse(false);
	upperAni[RATK]->SetDefault();
	upperAni[LATK]->SetDefaultReverse();
	upperAni[DIE]->SetDefault();
	upperAni[RUP]->SetDefault();
	upperAni[RUPIDLE]->SetDefault(true);
	upperAni[LUP]->SetDefaultReverse();
	upperAni[LUPIDLE]->SetDefaultReverse(true);
	upperAni[RUPFIRE]->SetDefault();
	upperAni[LUPFIRE]->SetDefaultReverse();
	upperAni[RDOWN]->SetDefault();
	upperAni[RDOWNIDLE]->SetDefault();
	upperAni[RDOWNMOVE]->SetDefault(true);
	upperAni[LDOWN]->SetDefaultReverse();
	upperAni[LDOWNIDLE]->SetDefaultReverse();
	upperAni[LDOWNMOVE]->SetDefaultReverse(true);
	upperAni[RDOWNFIRE]->SetDefault();
	upperAni[LDOWNFIRE]->SetDefaultReverse();
	upperAni[RDOWNATK]->SetDefault();
	upperAni[LDOWNATK]->SetDefaultReverse();
	upperAni[RDOWNBOMB]->SetDefault();
	upperAni[LDOWNBOMB]->SetDefaultReverse();
	upperAni[ITEMRIDLE]->SetDefault();
	upperAni[ITEMRRUN]->SetDefault();
	upperAni[ITEMRFIRE]->SetDefault();
	upperAni[ITEMLIDLE]->SetDefaultReverse();
	upperAni[ITEMLRUN]->SetDefaultReverse();
	upperAni[ITEMLFIRE]->SetDefaultReverse();
	upperAni[ITEMRUP]->SetDefault(true);
	upperAni[ITEMLUP]->SetDefaultReverse(true);
	upperAni[ITEMRUPFIRE]->SetDefault();
	upperAni[ITEMLUPFIRE]->SetDefaultReverse();
	upperAni[ITEMRBOMB]->SetDefault();
	upperAni[ITEMLBOMB]->SetDefaultReverse();
	upperAni[ITEMRDOWNIDLE]->SetDefault(true);
	upperAni[ITEMRDOWNMOVE]->SetDefault(true);
	upperAni[ITEMRDOWNFIRE]->SetDefault();
	upperAni[ITEMLDOWNIDLE]->SetDefault(true);
	upperAni[ITEMLDOWNMOVE]->SetDefault(true);
	upperAni[ITEMLDOWNFIRE]->SetDefault();
	upperAni[ITEMRDOWNATK]->SetDefault();
	upperAni[ITEMLDOWNATK]->SetDefaultReverse();
	upperAni[ITEMRDOWNBOMB]->SetDefault();
	upperAni[ITEMLDOWNBOMB]->SetDefaultReverse();

	upperAni[RFIRE]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[LFIRE]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[RUPFIRE]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[LUPFIRE]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[RBOMB]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[LBOMB]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[RDOWNBOMB]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[LDOWNBOMB]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[RATK]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[LATK]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[RUP]->SetEndEvent(bind(&Player::SetIsUp, this));
	upperAni[LUP]->SetEndEvent(bind(&Player::SetIsUp, this));
	upperAni[RDOWN]->SetEndEvent(bind(&Player::SetIsDown, this));
	upperAni[LDOWN]->SetEndEvent(bind(&Player::SetIsDown, this));
	upperAni[RDOWNFIRE]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[LDOWNFIRE]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[RDOWNATK]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[LDOWNATK]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[ITEMRFIRE]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[ITEMLFIRE]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[ITEMRUPFIRE]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[ITEMLUPFIRE]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[ITEMRDOWNFIRE]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[ITEMLDOWNFIRE]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[ITEMRDOWNATK]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[ITEMLDOWNATK]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[ITEMRDOWNBOMB]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[ITEMLDOWNBOMB]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[ITEMRBOMB]->SetEndEvent(bind(&Player::SetAction, this));
	upperAni[ITEMLBOMB]->SetEndEvent(bind(&Player::SetAction, this));
}

void Player::InitLowerMotion()
{
	Image* image = IMAGE->Add(L"Images/LowerBody - RightIdle.bmp", 100, 64, 1, 1);
	lowerBody.push_back(image);
	lowerAni.push_back(new Animation(image, 0.05f));

	image = IMAGE->Add(L"Images/LowerBody - RightRun.bmp", 1200, 64, 12, 1);
	lowerBody.push_back(image);
	lowerAni.push_back(new Animation(image, 0.05f));

	image = IMAGE->Add(L"Images/LowerBody - LeftIdle.bmp", 100, 64, 1, 1);
	lowerBody.push_back(image);
	lowerAni.push_back(new Animation(image, 0.05f));

	image = IMAGE->Add(L"Images/LowerBody - LeftRun.bmp", 1200, 64, 12, 1);
	lowerBody.push_back(image);
	lowerAni.push_back(new Animation(image, 0.05f));

	image = IMAGE->Add(L"Images/LowerBody - RightJump.bmp", 600, 100, 6, 1);
	lowerBody.push_back(image);
	lowerAni.push_back(new Animation(image, 0.08f));

	image = IMAGE->Add(L"Images/LowerBody - LeftJump.bmp", 600, 100, 6, 1);
	lowerBody.push_back(image);
	lowerAni.push_back(new Animation(image, 0.08f));

	

	lowerAni[RIDLE]->SetDefault(true);
	lowerAni[RRUN]->SetDefault(true);
	lowerAni[RRUN]->Play();
	lowerAni[LIDLE]->SetDefaultReverse(true);
	lowerAni[LRUN]->SetDefaultReverse(true);
	lowerAni[LRUN]->Play();
	lowerAni[RJUMP]->SetDefault(false);
	lowerAni[LJUMP]->SetDefaultReverse(false);
}

void Player::SetDie()
{
	if (life >= 0)
	{
		for (Enemy* enemy : em->GetEnemy())
		{
			if (enemy->GetSword()->GetIsActive() && !isDie && enemy->GetSword()->GetGravity() < 0)
			{
				Rect box = enemy->GetSwordRect();
				Bomb* temp = NULL;

				float minX = min(hitBox->Right(), box.Right());
				float maxX = max(hitBox->Left(), box.Left());

				float minY = min(hitBox->Bottom(), box.Bottom());
				float maxY = max(hitBox->Top(), box.Top());

				Vector pos;
				pos.x = minX - maxX;
				pos.y = minY - maxY;

				if (pos.x > 0 && pos.y > 0)
				{
					life--;
					SOUND->Play("PlayerDie");
					isDie = true;
					enemy->GetSword()->SetIsActive();
					SetUp(DIE);
				}
			}
		}


		for (TankBullet* bullet : em->GetTank()->GetTankBullet())
		{
			if (bullet->GetIsActive() && !isDie)
			{
				Rect box = bullet->GetRect();
				Bomb* temp = NULL;


				float minX = min(hitBox->Right(), box.Right());
				float maxX = max(hitBox->Left(), box.Left());

				float minY = min(hitBox->Bottom(), box.Bottom());
				float maxY = max(hitBox->Top(), box.Top());

				Vector pos;
				pos.x = minX - maxX;
				pos.y = minY - maxY;

				if (pos.x > 0 && pos.y > 0 && !isDown)
				{
					life--;
					SOUND->Play("PlayerDie");
					isDie = true;
					bullet->SetIsActive();
					SetUp(DIE);
				}
			}
		}

		if (isDie)
		{
			if (!bodyAni[1]->GetIsPlay())
			{
				Reset();
			}
		}
	}
	else
	{
		if (!bodyAni[1]->GetIsPlay())
		{
			SOUND->Stop("TankMove");
			SOUND->Stop("bgm");
			SOUND->Play("Lose");
			SCENE->ChangeScene("GameOver");
		}
	}
}

void Player::Reset()
{
	resetTime += 1;
	if (resetTime > 100)
	{
		resetTime = 0;
		isDie = false;
		isAction = false;
		SetUp(RIDLE);
	}
}
