#include "framework.h"

EnemyManager::EnemyManager(int enemyCount)
{
	spawnTime = 0.0f;

	for (int i = 0; i < enemyCount; i++)
	{
		enemies.push_back(new Enemy());
	}
	tank = new Tank();
}

EnemyManager::~EnemyManager()
{
	for (Enemy* enemy : enemies)
		delete enemy;
	delete tank;
}

void EnemyManager::Update()
{
	for (Enemy* enemy : enemies)
		enemy->Update();
	PlayEnemy();
	tank->Update();
}

void EnemyManager::Render(HDC hdc)
{
	for (Enemy* enemy : enemies)
		enemy->Render(hdc);
	tank->Render(hdc);
}

void EnemyManager::PlayEnemy()
{
	spawnTime += 0.05f;

	if (spawnTime > SPAWNDELAY)
	{
		spawnTime = 0.0f;
		for (Enemy* enemy : enemies)
		{
			if (!enemy->GetIsActive())
			{
				enemy->Play(player->GetRect());
				break;
			}
		}
	}
}