#pragma once
#include "Entity2D.h"
#include "AllManager.h"


// --- 画像読み込み関係 ---
void bowlImage();

// --- リセット関数（初期配置や状態の初期化） ---
void bowlReset();

void checkbowlCollider(Entity2D& entity, int i);

// --- 描画関数 ---
void bowlDraw();

// --- 解放関数 ---
void bowlDelete();
