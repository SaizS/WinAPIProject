#include "framework.h"

PlayScene::PlayScene()
{
	Image* image = IMAGE->Add(L"Images/explosion.bmp", 491, 477, 5, 5, BLACK);
	player = new Player();
	em = new EnemyManager(10);
	bg = new BackGround();
	hm = new HubManager();
	npc = new Npc();

	colllsionLand = IMAGE->Add(L"Images/landCollision.bmp", 1176, 224, MAGENTA);

	player->SetCollision(colllsionLand);
	player->SetBackGround(bg);
	player->SetEnemy(em);
	em->SetPlayer(player);
	hm->SetPlayer(player);
	npc->SetPlayer(player);

	LoadSound();
	LoadEffect();
}

PlayScene::~PlayScene()
{
	delete player;
	delete em;
	delete bg;
	delete hm;
	delete npc;
}

void PlayScene::Init()
{
}

void PlayScene::Update()
{
	player->Update();
	em->Update();
	hm->Update();
	npc->Update();
}

void PlayScene::Render(HDC hdc)
{
	bg->Render(hdc); 
	player->Render(hdc);
	em->Render(hdc);
	hm->Render(hdc);
	npc->Render(hdc);
}

void PlayScene::Release()
{
}

void PlayScene::LoadSound()
{
	SOUND->Add("bgm", "Sounds/stage.mp3", true);
	SOUND->Add("basic", "Sounds/BasicGun.mp3", false);
	SOUND->Add("hit", "Sounds/HitSound.mp3", false);
	SOUND->Add("attack", "Sounds/attack.mp3", false);
	SOUND->Add("EnemyDie1", "Sounds/EnemyDie1.mp3", false);
	SOUND->Add("EnemyDie2", "Sounds/EnemyDie2.mp3", false);
	SOUND->Add("bomb", "Sounds/bomb3.wav", false);
	SOUND->Add("PlayerDie", "Sounds/PlayerDie.mp3", false);
	SOUND->Add("TankMove", "Sounds/TankMove.mp3", true);
	SOUND->Add("TankFireReady", "Sounds/TankFireReady.mp3", false);
	SOUND->Add("TankFire", "Sounds/TankFire.mp3", false);
	SOUND->Add("ItemFire", "Sounds/Item.mp3", false);
	SOUND->Add("frame", "Sounds/frame.mp3", false);
	SOUND->Add("Npc - Bye", "Sounds/Npc - Bye.wma", false);
	SOUND->Add("Npc - Give", "Sounds/Npc - Give.wma", false);
	SOUND->Add("EatFrame", "Sounds/EatFrame.mp3", false);
	SOUND->Add("EatBomb", "Sounds/EatBomb.mp3", false);
	SOUND->Add("Lose", "Sounds/Lose.mp3", false);
	SOUND->Add("Destroy", "Sounds/Destroy.mp3", false);
}

void PlayScene::LoadEffect()
{
	Image* image = IMAGE->Add(L"Images/Effect/bomb.bmp", 1350, 100, 27, 1);
	EFFECT->Add("bomb", image, { 100,100 }, 5, 0.03f);
	image = IMAGE->Add(L"Images/Effect/UpFire.bmp", 66, 27, 3, 1);
	EFFECT->Add("UpFire", image, { 50,50 }, 5, 0.03f);
	image = IMAGE->Add(L"Images/Effect/Tank - Fire.bmp", 1020, 46, 17, 1);
	EFFECT->Add("TankFire", image, { 100, 100 }, 5, 0.03f);
}
