#pragma once
#include "Entity2D.h"



// --- 画像読み込み関係 ---
void hookImage();

// --- リセット関数（初期配置や状態の初期化） ---
void hookReset(DxPlus::Vec2 playerBasePosition);

// --- 動きの更新 ---
void Updatehook(float deltaTime,int x ,int y,DxPlus::Vec2 pointer, bool left);

void checkHookCollider(const DxPlus::Vec2& targetPos, float targetRadius, int i,bool veg);

// --- 描画関数 ---
void hookDraw(bool left);

// --- 解放関数 ---
void hookDelete();
