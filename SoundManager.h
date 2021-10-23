#pragma once

#define SOUNDCOUNT 10

using namespace FMOD;

struct SoundInfo
{
	Sound* sound;
	Channel* channel;

	SoundInfo() : sound(NULL), channel(NULL) 
	{};
	~SoundInfo()
	{
		sound->release();
	}
};

class SoundManager
{
private:
	System* soundSystem;
	map<string, SoundInfo*> totalSound;
	static SoundManager* instance;

	SoundManager();
	~SoundManager();

public:
	static SoundManager* GetInstance();
	static void Create();
	static void Delete();

	void Update();

	void Add(string key, string fileName, bool bgm);

	void Play(string key, float volume = 1.0f);
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);
	bool GetPlay(string key);
};