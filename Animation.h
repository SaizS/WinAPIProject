#pragma once

class Animation
{
private:
	vector<POINT> frames;
	vector<int> action;

	int curPlayNum;
	int maxPlayNum;

	POINT maxFrame;

	bool isPlay;
	bool isLoop;
	bool isPingpong;

	float time;
	float frameUpdateSec;
	
	function<void()> EndEvent;
public:
	Animation(Image* image, float speed = 0.1f);
	~Animation();

	void Update();

	void SetDefault(bool loop = false, bool pinpong = false);
	void SetDefaultReverse(bool loop = false, bool pinpong = false);
	void SetArray(int* actArr, int arrSize, bool loop = false, bool pingpong = false);
	void SetPart(int start, int end, bool loop = false, bool pingpong = false);

	void SetPingpong();

	void Play()
	{
		isPlay = true;
		curPlayNum = 0;
	}

	void Stop() { isPlay = false; }	

	bool GetIsPlay() { return isPlay; }
	POINT GetFrame() { return frames[action[curPlayNum]]; }

	void SetEndEvent(function<void()> Event) { EndEvent = Event; }
};