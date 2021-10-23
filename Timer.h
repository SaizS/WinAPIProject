#pragma once

class Timer
{
private:
	static Timer* instance;

	float timeScale;
	float timeElapsed;

	__int64 curTime;
	__int64 lastTime;
	__int64 periodFrequency; // ºóµµ¼ö

	UINT frameRate;
	UINT frameCount;

	float oneSecCount;
	float worldTime;
	float lockFPS;

	Timer();
	~Timer();
public:
	static Timer* GetInstanse();
	static void Create();
	static void Delete();

	void Update();
	void Render(HDC hdc);

	UINT GetFPS() { return frameRate; }
	float GetElapsedTime() { return timeElapsed; }
	float GetWorldTime() { return worldTime; }
};