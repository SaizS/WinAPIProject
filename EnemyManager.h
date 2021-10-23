#pragma once

#define SPAWNDELAY 3.0f

class EnemyManager
{
private:
	vector<Enemy*> enemies;
	Tank* tank;

	float spawnTime;

	Player* player;
public:
	EnemyManager(int enemyCount);
	~EnemyManager();

	void Update();
	void Render(HDC hdc);

	void PlayEnemy();

	void SetPlayer(Player* player) { this->player = player; }

	vector<Enemy*> GetEnemy() { return enemies; }
	Tank* GetTank() { return tank; }
};