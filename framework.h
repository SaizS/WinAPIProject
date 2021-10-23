// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#define WIN_WIDTH 1176
#define WIN_HEIGHT 448

#define WIN_START_X 300
#define WIN_START_Y 300

#define TIMER Timer::GetInstanse()
#define DELTATIME Timer::GetInstanse()->GetElapsedTime()
#define KEYBOARD Keyboard::GetInstance()
#define IMAGE ImageManager::GetInstance()
#define SOUND SoundManager::GetInstance()
#define EFFECT EffectManager::GetInstance()
#define SCENE SceneManager::GetInstance()

#define PI 3.14f

// Windows 헤더 파일
#include <windows.h>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>
#include <bitset>
#include <map>
#include <functional>

using namespace std;

#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmod_vc.lib")

enum Color
{
	RED = RGB(255, 0, 0),
	GREEN = RGB(0, 255, 0),
	BLUE = RGB(0, 0, 255),
	YELLOW = RGB(255, 255, 0),
	WHITE = RGB(255, 255, 255),
	BLACK = RGB(0, 0, 0),
	MAGENTA = RGB(255, 0, 255),
	CYAN = RGB(0, 255, 255)
};

//FrameWork Header File
#include "Image.h"
#include "ImageManager.h"
#include "Animation.h"
#include "Vector.h"
#include "Rect.h"
#include "Math.h"
#include "Timer.h"
#include "Keyboard.h"
#include "SoundManager.h"
#include "Effect.h"
#include "EffectManager.h"
#include "Scene.h"
#include "SceneManager.h"

//Object Header File
#include "Info.h"
#include "Sword.h"
#include "Enemy.h"
#include "TankBullet.h"
#include "Tank.h"
#include "EnemyManager.h"
#include "Bullet.h"
#include "ItemBullet.h"
#include "FrameBullet.h"
#include "Bomb.h"
#include "Sky.h"
#include "Land.h"
#include "BackGround.h"
#include "ScoreHub.h"
#include "WeaponHub.h"
#include "HubManager.h"
#include "Player.h"
#include "FrameItem.h"
#include "BombItem.h"
#include "Npc.h"

//Test Header File
#include "StartScene.h"
#include "PlayScene.h"
#include "GameOver.h"
#include "GameManager.h"

extern HINSTANCE hInst;
extern HWND hWnd;
extern Vector mousePos;
extern int moveDistance;
extern int score;