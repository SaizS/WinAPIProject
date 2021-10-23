#include "framework.h"

WeaponHub::WeaponHub()
{
	weapon = IMAGE->Add(L"Images/Hub/WeaponHub.bmp", 62, 17);
	rect = new Rect(320, 60, 186, 51);

	for (int i = 0; i < 10; i++)
	{
		wstring str = L"Images/Number/Weapon/" + to_wstring(i) + L".bmp";
		Image* image = IMAGE->Add(str.c_str(), 8, 8);
		numbers.push_back(image);
	}

	for (int i = 0; i < 2; i++)
	{
		bombNum.push_back(numbers[0]);
		bombRect.push_back(new Rect(355 + (i * 24), 70, 24, 24));
		frameNum.push_back(numbers[0]);
		frameRect.push_back(new Rect(283 + (i * 24), 70, 24, 24));
	}

	basicBullet = IMAGE->Add(L"Images/Number/basic.bmp", 20, 8);
	basicRect = new Rect(283, 70, 60, 24);
}

WeaponHub::~WeaponHub()
{
	delete rect;
	delete basicRect;

	for (Rect* rc : bombRect)
		delete rc;

	for (Rect* rc : frameRect)
		delete rc;
}

void WeaponHub::Render(HDC hdc)
{
	weapon->Render(hdc, *rect);

	if (bombNum[0] != numbers[0])
		bombNum[0]->Render(hdc, *bombRect[0]);
	bombNum[1]->Render(hdc, *bombRect[1]);

	if(frameNum[0] == numbers[0] && frameNum[1] == numbers[0])
		basicBullet->Render(hdc, *basicRect);
	else
	{
		if (frameNum[0] != numbers[0])
			frameNum[0]->Render(hdc, *frameRect[0]);
		frameNum[1]->Render(hdc, *frameRect[1]);
	}
}

void WeaponHub::SetNumber(Player* player)
{
	int val = player->GetBomb();

	if (val >= 10)
	{
		switch (val/10)
		{
		case 1:
			bombNum[0] = numbers[1];
			break;
		case 2:
			bombNum[0] = numbers[2];
			break;
		case 3:
			bombNum[0] = numbers[3];
			break;
		case 4:
			bombNum[0] = numbers[4];
			break;
		case 5:
			bombNum[0] = numbers[5];
			break;
		case 6:
			bombNum[0] = numbers[6];
			break;
		case 7:
			bombNum[0] = numbers[7];
			break;
		case 8:
			bombNum[0] = numbers[8];
			break;
		case 9:
			bombNum[0] = numbers[9];
			break;
		default:
			break;
		}

		val = val - (val / 10 * 10);
		switch (val)
		{
		case 1:
			bombNum[1] = numbers[1];
			break;
		case 2:
			bombNum[1] = numbers[2];
			break;
		case 3:
			bombNum[1] = numbers[3];
			break;
		case 4:
			bombNum[1] = numbers[4];
			break;
		case 5:
			bombNum[1] = numbers[5];
			break;
		case 6:
			bombNum[1] = numbers[6];
			break;
		case 7:
			bombNum[1] = numbers[7];
			break;
		case 8:
			bombNum[1] = numbers[8];
			break;
		case 9:
			bombNum[1] = numbers[9];
			break;
		case 0:
			bombNum[1] = numbers[0];
			break;
		default:
			break;
		}
	}
	else
	{
		bombNum[0] = numbers[0];

		switch (val)
		{
		case 1:
			bombNum[1] = numbers[1];
			break;
		case 2:
			bombNum[1] = numbers[2];
			break;
		case 3:
			bombNum[1] = numbers[3];
			break;
		case 4:
			bombNum[1] = numbers[4];
			break;
		case 5:
			bombNum[1] = numbers[5];
			break;
		case 6:
			bombNum[1] = numbers[6];
			break;
		case 7:
			bombNum[1] = numbers[7];
			break;
		case 8:
			bombNum[1] = numbers[8];
			break;
		case 9:
			bombNum[1] = numbers[9];
			break;
		case 0:
			bombNum[1] = numbers[0];
			break;
		default:
			break;
		}
	}
}

void WeaponHub::SetFrameNumber(Player* player)
{
	int val = player->GetFrameBullet();

	if (val == 0)
	{
		frameNum[0] = numbers[0];
		frameNum[1] = numbers[0];
	}
	else
	{
		if (val >= 10)
		{
			switch (val/10)
			{
			case 1:
				frameNum[0] = numbers[1];
				break;
			case 2:
				frameNum[0] = numbers[2];
				break;
			case 3:
				frameNum[0] = numbers[3];
				break;
			case 4:
				frameNum[0] = numbers[4];
				break;
			case 5:
				frameNum[0] = numbers[5];
				break;
			case 6:
				frameNum[0] = numbers[6];
				break;
			case 7:
				frameNum[0] = numbers[7];
				break;
			case 8:
				frameNum[0] = numbers[8];
				break;
			case 9:
				frameNum[0] = numbers[9];
				break;
			case 0:
				frameNum[0] = numbers[0];
				break;
			default:
				break;
			}

			val = val - (val / 10 * 10);

			switch (val)
			{
			case 1:
				frameNum[1] = numbers[1];
				break;
			case 2:
				frameNum[1] = numbers[2];
				break;
			case 3:
				frameNum[1] = numbers[3];
				break;
			case 4:
				frameNum[1] = numbers[4];
				break;
			case 5:
				frameNum[1] = numbers[5];
				break;
			case 6:
				frameNum[1] = numbers[6];
				break;
			case 7:
				frameNum[1] = numbers[7];
				break;
			case 8:
				frameNum[1] = numbers[8];
				break;
			case 9:
				frameNum[1] = numbers[9];
				break;
			case 0:
				frameNum[1] = numbers[0];
				break;
			default:
				break;
			}
		}
		else
		{
			frameNum[0] = numbers[0];
			switch (val)
			{
			case 1:
				frameNum[1] = numbers[1];
				break;
			case 2:
				frameNum[1] = numbers[2];
				break;
			case 3:
				frameNum[1] = numbers[3];
				break;
			case 4:
				frameNum[1] = numbers[4];
				break;
			case 5:
				frameNum[1] = numbers[5];
				break;
			case 6:
				frameNum[1] = numbers[6];
				break;
			case 7:
				frameNum[1] = numbers[7];
				break;
			case 8:
				frameNum[1] = numbers[8];
				break;
			case 9:
				frameNum[1] = numbers[9];
				break;
			case 0:
				frameNum[1] = numbers[0];
				break;
			default:
				break;
			}
		}
	}
}
