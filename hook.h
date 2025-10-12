#pragma once
#include "Entity2D.h"



// --- 画像読み込み関係 ---
void hookImage();

// --- リセット関数（初期配置や状態の初期化） ---
void hookReset(DxPlus::Vec2 playerBasePosition);

// --- 動きの更新 ---
void Updatehook(float deltaTime,int x ,int y);


// --- 描画関数 ---
void hookDraw()
;

// --- 解放関数 ---
void hookDelete();
