#pragma once

#include "Entity2D.h"


// --- 画像読み込み関係 ---
void EnemyImage();

// --- リセット関数（初期配置や状態の初期化） ---
void EnemyReset();



// --- 動きの更新 ---
void UpdateEnemy(int i, float deltaTime,HookState& hookState);

void SpawnTimeEnemy(int i, int* Timer);

void onHookEnemyHit(const DxPlus::Vec2& targetPos, Entity2D* hook, int i);

// --- 描画関数 ---
void EnemyDraw(int i);

// --- 解放関数 ---
void EnemyDelete(int i);
