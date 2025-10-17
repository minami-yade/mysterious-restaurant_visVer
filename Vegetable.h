#pragma once
#include "Entity2D.h"


// --- 画像読み込み関係 ---
void VegetableImage();

// --- リセット関数（初期配置や状態の初期化） ---
void VegetableReset();

// --- 動きの更新（単純な三角波で上下） ---
void UpdateVegetable(int i,float deltaTime,HookState hookState);

// 画面外からランダムに出現

void SpawnTimeVegetable(int i, int* Timer);


void onHookHit(const DxPlus::Vec2& targetPos, Entity2D* hook, Entity2D* player, int i);


// --- 描画関数 ---
void VegetableDraw(int i);

// --- 解放関数 ---
void VegetableDelete(int i);

