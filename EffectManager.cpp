#include "framework.h"

EffectManager* EffectManager::instance = NULL;

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
	for (auto effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			delete effect;
	}
}

EffectManager* EffectManager::GetInstance()
{
	return instance;
}

void EffectManager::Create()
{
	instance = new EffectManager();
}

void EffectManager::Delete()
{
	delete instance;
}

void EffectManager::Update()
{
	for (auto effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			effect->Update();
	}
}

void EffectManager::Render(HDC hdc)
{
	for (auto effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			effect->Render(hdc);
	}
}

void EffectManager::Add(string key, wstring fileName, int width, int height, int frameX, int frameY, Vector size, COLORREF transColor, int poolCount, float speed)
{
	Image* texture = IMAGE->Add(fileName, width, height, frameX, frameY, transColor);

	Effects effects;
	for (int i = 0; i < poolCount; i++)
	{
		effects.push_back(new Effect(texture, size, speed));
	}

	totalEffect.insert({ key, effects });
}

void EffectManager::Add(string key, Image* texture, Vector size, int poolCount, float speed)
{
	Effects effects;
	for (int i = 0; i < poolCount; i++)
	{
		effects.push_back(new Effect(texture, size, speed));
	}

	totalEffect.insert({ key, effects });
}

void EffectManager::Start(string key, Vector pos)
{
	if (totalEffect.count(key) == 0)
		return;

	for (Effect* effect : totalEffect[key])
	{
		if (!effect->GetIsActive())
		{
			effect->Start(pos);
			return;
		}
	}
}
