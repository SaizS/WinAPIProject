#include "framework.h"

ScoreHub::ScoreHub()
{
	scoreHub = IMAGE->Add(L"Images/Hub/ScoreHub.bmp", 58, 24);
	rect = new Rect(120, 60, 174, 72);

	for (int i = 0; i < 10; i++)
	{
		wstring str = L"Images/Number/Score/" + to_wstring(i) + L".bmp";
		Image* image = IMAGE->Add(str.c_str(), 8, 8);
		numbers.push_back(image);
	}

	for (int i = 0; i < 7; i++)
	{
		scoreNum.push_back(numbers[0]);
		scoreRect.push_back(new Rect(50+(i*24), 36, 24, 24));
	}

	for (int i = 0; i < 3; i++)
	{
		wstring str = L"Images/Number/Life/" + to_wstring(i) + L".bmp";
		Image* image = IMAGE->Add(str.c_str(), 8, 8);
		lifeNumbers.push_back(image);
	}

	lifeNum = IMAGE->Add(L"Images/Number/Life/0.bmp", 8, 8);
	lifeRect = new Rect(146, 84, 24, 24);
}

ScoreHub::~ScoreHub()
{
	delete rect;

	for (Rect* rc : scoreRect)
		delete rc;
}

void ScoreHub::Update()
{
}

void ScoreHub::Render(HDC hdc)
{
	scoreHub->Render(hdc, *rect);

	for (int i = 0; i < 7; i++)
	{
		scoreNum[i]->Render(hdc, *scoreRect[i]);
	}
	lifeNum->Render(hdc, *lifeRect);
}

void ScoreHub::InitNumber()
{
}

void ScoreHub::SetScore()
{
	int val = score;
	if (val > 10000)
	{	
			switch (val / 10000)
			{
			case 0:
				scoreNum[2] = numbers[0];
				break;
			case 1:
				scoreNum[2] = numbers[1];
				break;
			case 2:
				scoreNum[2] = numbers[2];
				break;
			case 3:
				scoreNum[2] = numbers[3];
				break;
			case 4:
				scoreNum[2] = numbers[4];
				break;
			case 5:
				scoreNum[2] = numbers[5];
				break;
			case 6:
				scoreNum[2] = numbers[6];
				break;
			case 7:
				scoreNum[2] = numbers[7];
				break;
			case 8:
				scoreNum[2] = numbers[8];
				break;
			case 9:
				scoreNum[2] = numbers[9];
				break;
			default:
				break;
			}

			val = val - ((val / 10000) * 10000);

			switch (val / 1000)
			{
			case 0:
				scoreNum[3] = numbers[0];
				break;
			case 1:
				scoreNum[3] = numbers[1];
				break;
			case 2:
				scoreNum[3] = numbers[2];
				break;
			case 3:
				scoreNum[3] = numbers[3];
				break;
			case 4:
				scoreNum[3] = numbers[4];
				break;
			case 5:
				scoreNum[3] = numbers[5];
				break;
			case 6:
				scoreNum[3] = numbers[6];
				break;
			case 7:
				scoreNum[3] = numbers[7];
				break;
			case 8:
				scoreNum[3] = numbers[8];
				break;
			case 9:
				scoreNum[3] = numbers[9];
				break;
			default:
				break;
			}
			val = val - ((val / 1000) * 1000);

			switch (val / 100)
			{
			case 0:
				scoreNum[4] = numbers[0];
				break;
			case 1:
				scoreNum[4] = numbers[1];
				break;
			case 2:
				scoreNum[4] = numbers[2];
				break;
			case 3:
				scoreNum[4] = numbers[3];
				break;
			case 4:
				scoreNum[4] = numbers[4];
				break;
			case 5:
				scoreNum[4] = numbers[5];
				break;
			case 6:
				scoreNum[4] = numbers[6];
				break;
			case 7:
				scoreNum[4] = numbers[7];
				break;
			case 8:
				scoreNum[4] = numbers[8];
				break;
			case 9:
				scoreNum[4] = numbers[9];
				break;
			default:
				break;
			}
	}
	else if(val > 1000)
	{
		switch (val / 1000)
		{
		case 0:
			scoreNum[3] = numbers[0];
			break;
		case 1:
			scoreNum[3] = numbers[1];
			break;
		case 2:
			scoreNum[3] = numbers[2];
			break;
		case 3:
			scoreNum[3] = numbers[3];
			break;
		case 4:
			scoreNum[3] = numbers[4];
			break;
		case 5:
			scoreNum[3] = numbers[5];
			break;
		case 6:
			scoreNum[3] = numbers[6];
			break;
		case 7:
			scoreNum[3] = numbers[7];
			break;
		case 8:
			scoreNum[3] = numbers[8];
			break;
		case 9:
			scoreNum[3] = numbers[9];
			break;
		default:
			break;
		}

		val = val - ((val / 1000) * 1000);

		switch (val / 100)
		{
		case 0:
			scoreNum[4] = numbers[0];
			break;
		case 1:
			scoreNum[4] = numbers[1];
			break;
		case 2:
			scoreNum[4] = numbers[2];
			break;
		case 3:
			scoreNum[4] = numbers[3];
			break;
		case 4:
			scoreNum[4] = numbers[4];
			break;
		case 5:
			scoreNum[4] = numbers[5];
			break;
		case 6:
			scoreNum[4] = numbers[6];
			break;
		case 7:
			scoreNum[4] = numbers[7];
			break;
		case 8:
			scoreNum[4] = numbers[8];
			break;
		case 9:
			scoreNum[4] = numbers[9];
			break;
		default:
			break;
		}
	}
	else if (val > 100)
	{
		switch (val / 100)
		{
		case 0:
			scoreNum[4] = numbers[0];
			break;
		case 1:
			scoreNum[4] = numbers[1];
			break;
		case 2:
			scoreNum[4] = numbers[2];
			break;
		case 3:
			scoreNum[4] = numbers[3];
			break;
		case 4:
			scoreNum[4] = numbers[4];
			break;
		case 5:
			scoreNum[4] = numbers[5];
			break;
		case 6:
			scoreNum[4] = numbers[6];
			break;
		case 7:
			scoreNum[4] = numbers[7];
			break;
		case 8:
			scoreNum[4] = numbers[8];
			break;
		case 9:
			scoreNum[4] = numbers[9];
			break;
		default:
			break;
		}
	}
}

void ScoreHub::SetLife(int life)
{
	switch (life)
	{
	case 0:
		lifeNum = lifeNumbers[0];
		break;
	case 1:
		lifeNum = lifeNumbers[1];
		break;
	case 2:
		lifeNum = lifeNumbers[2];
		break;
	default:
		break;
	}
}
