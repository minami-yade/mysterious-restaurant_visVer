#pragma once
#include "DxPlus/DxPlus.h"

struct Entity2D
{
    //位置関係
    DxPlus::Vec2 position = {};
    DxPlus::Vec2 velocity = {};
    //画像
    int spriteID = -1;
	DxPlus::Vec2 scale = { 1.0f, 1.0f };
	DxPlus::Vec2 Center = { 64.0f, 64.0f };


    //player
    int score = 0;
    //Vegetable
    int havescore = 0;
	bool isActive = false;
	float speed = 0.0f;
	int type = 0; //　0:キャベツ
    float  baseY;        // 基準高
    float amplitude;    // 振幅（最大高さ - baseY）
    float period;       // 周期（秒）
    float timeAcc = 0;  // 累積時間（内部で管理）

};
const int PLAYER_NUM = 9;

const int VEGETABLE_NUM = 12;
const int VEGETABLE_TYPE = 1; // 0:キャベツ