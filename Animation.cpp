#include "framework.h"

Animation::Animation(Image* image, float speed)
	: time(0.0f), frameUpdateSec(speed), isLoop(false), isPingpong(false)
{
	maxFrame = image->GetFrame();
	maxPlayNum = maxFrame.x * maxFrame.y;

	for (int i = 0; i < maxFrame.y; i++)
	{
		for (int j = 0; j < maxFrame.x; j++)
		{
			frames.push_back({ j,i });
		}
	}
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (!isPlay)
		return;

	time += DELTATIME;

	if (time > frameUpdateSec)
	{
		time -= frameUpdateSec;
		curPlayNum++;

		if (curPlayNum > action.size() - 1)
		{
			if (isLoop)
			{
				curPlayNum = 0;
			}
			else
			{
				curPlayNum--;
				isPlay = false;
				if (EndEvent != NULL)
					EndEvent();
			}
		}
	}
}

void Animation::SetDefault(bool loop, bool pinpong)
{
	isLoop = loop;
	isPingpong = pinpong;
	
	action.clear();

	for (int i = 0; i < maxPlayNum; i++)
	{
		action.push_back(i);
	}

	SetPingpong();
}

void Animation::SetDefaultReverse(bool loop, bool pinpong)
{
	isLoop = loop;
	isPingpong = pinpong;

	action.clear();

	for (int i = maxPlayNum-1; i >= 0; i--)
	{
		action.push_back(i);
	}

	SetPingpong();
}

void Animation::SetArray(int* actArr, int arrSize, bool loop, bool pingpong)
{
	isLoop = loop;
	isPingpong = pingpong;
	
	action.clear();

	for (int i = 0; i < arrSize; i++)
		action.push_back(actArr[i]);

	SetPingpong();
}

void Animation::SetPart(int start, int end, bool loop, bool pingpong)
{
	isLoop = loop;
	isPingpong = pingpong;

	action.clear();
	
	for (int i = start; i <= end; i++)
		action.push_back(i);

	SetPingpong();
}

void Animation::SetPingpong()
{
	if (isPingpong)
	{
		for (int i = action.size() - 2; i >= 0; i--)
			action.push_back(action[i]);
	}
}
