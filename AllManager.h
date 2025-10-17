#pragma once
#include "player.h"
#include "Back.h"
#include "Vegetable.h"
#include "Enemy.h"
#include "hook.h"



void GameAllLoad();
void GameAllDelete();
float GetDeltaTime_DxLib(int g_prevMs);
void AllChackCollider();
DxPlus::Vec2 randamSpawn();


