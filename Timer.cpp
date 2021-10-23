#include "framework.h"

Timer* Timer::instance = NULL;

Timer::Timer() : frameRate(0), frameCount(0), timeElapsed(0.0f), oneSecCount(0.0f), worldTime(0.0f), lockFPS(60.0f)
{
	//1�ʵ��� CPU�� �������� ��ȯ�ϴ� �Լ�
	QueryPerformanceFrequency((LARGE_INTEGER*)& periodFrequency);

	//���� CPU�� ������
	QueryPerformanceCounter((LARGE_INTEGER*)& lastTime);

	timeScale = 1.0f / periodFrequency;
}

Timer::~Timer()
{
}

Timer* Timer::GetInstanse()
{
	return instance;
}

void Timer::Create()
{
	instance = new Timer();
}

void Timer::Delete()
{
	delete instance;
}

void Timer::Update()
{
	// ������ ���� �ð� ���ϱ�
	QueryPerformanceCounter((LARGE_INTEGER*)& curTime);

	timeElapsed = (curTime - lastTime) * timeScale;

	while (timeElapsed < (1.0f / lockFPS))
	{
		QueryPerformanceCounter((LARGE_INTEGER*)& curTime);

		timeElapsed = (curTime - lastTime) * timeScale;
	}

	lastTime = curTime;

	//////////////////////////////////////////////////////////////
	//FPS(Frame Per Second)

	frameCount++;
	oneSecCount += timeElapsed;

	if (oneSecCount >= 1.0f)
	{
		frameRate = frameCount;
		frameCount = 0;
		oneSecCount = 0.0f;
	}

	worldTime += timeElapsed;
}

void Timer::Render(HDC hdc)
{
	wstring str;

	str = L"FPS : " + to_wstring(frameRate);
	TextOut(hdc, 0, 0, str.c_str(), str.length());
	str = L"WorldTime : " + to_wstring(worldTime);
	TextOut(hdc, 0, 20, str.c_str(), str.length());
	str = L"ElapsedTime : " + to_wstring(timeElapsed);
	TextOut(hdc, 0, 40, str.c_str(), str.length());
}
