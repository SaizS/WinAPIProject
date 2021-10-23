#include "framework.h"

SoundManager* SoundManager::instance = NULL;

SoundManager::SoundManager()
{
	System_Create(&soundSystem);
	soundSystem->init(SOUNDCOUNT, FMOD_INIT_NORMAL, NULL);
}

SoundManager::~SoundManager()
{
	for (auto sound : totalSound)
		delete sound.second;
	soundSystem->release();
}

SoundManager* SoundManager::GetInstance()
{
	return instance;
}

void SoundManager::Create()
{
	instance = new SoundManager();
}

void SoundManager::Delete()
{
	delete instance;
}

void SoundManager::Update()
{
	soundSystem->update();
}

void SoundManager::Add(string key, string fileName, bool bgm)
{
	SoundInfo* info = new SoundInfo();

	if (bgm)
	{
		soundSystem->createStream(fileName.c_str(), FMOD_LOOP_NORMAL, NULL, &info->sound);
	}
	else
	{
		soundSystem->createStream(fileName.c_str(), FMOD_DEFAULT, NULL, &info->sound);
	}

	totalSound.insert({ key, info });
}

void SoundManager::Play(string key, float volume)
{
	if (totalSound[key] > 0)
	{
		soundSystem->playSound(totalSound[key]->sound, NULL, false, &totalSound[key]->channel);
		totalSound[key]->channel->setVolume(volume);
	}
}

void SoundManager::Stop(string key)
{
	if (totalSound[key] > 0)
	{
		totalSound[key]->channel->stop();
	}
}

void SoundManager::Pause(string key)
{
	if (totalSound[key] > 0)
	{
		totalSound[key]->channel->setPaused(true);
	}
}

void SoundManager::Resume(string key)
{
	if (totalSound[key] > 0)
	{
		totalSound[key]->channel->setPaused(false);
	}
}

bool SoundManager::GetPlay(string key)
{
	if (totalSound[key] > 0)
	{
		bool isPlay;
		totalSound[key]->channel->isPlaying(&isPlay);
		return isPlay;
	}
}
