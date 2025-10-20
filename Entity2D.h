#pragma once
#include "DxPlus/DxPlus.h"



struct Entity2D
{
    //位置関係
    DxPlus::Vec2 position = {};
    DxPlus::Vec2 velocity = {};
	float gravity = 0.98f; // 重力加速度
	float speed = 0.0f;

    //画像
    int spriteID = -1;
	DxPlus::Vec2 scale = { 1.0f, 1.0f };
	DxPlus::Vec2 center = { 64.0f, 64.0f };
	bool isActive = false;
	float radius = 30.0f; // 当たり判定用の半径
	
	//フックで使う
	float angle = 0;
	DxPlus::Vec2 target = {};
	DxPlus::Vec2 HomePositionLeft = {};
	DxPlus::Vec2 HomePositionRight = {};
	bool isCarryingVegetable = false;
	Entity2D* carriedVegetable = nullptr; // ポインタに変更
	DxPlus::Vec2 upHookLeft = {};
	DxPlus::Vec2 upHookRight = {};
	bool reachedUpHook = false;

    //Vegetable
    int havescore = 0;
	float  baseY = {};        // 基準高
	float JumpPower = 10.0f;
	int moveVegetable = 0;//0通常,1フックに捕まった,2フックに捕まった後放たれた


	//mouse
	bool click = false;
	float timer = 0.0f;
	DxPlus::Vec2 pointer = { 0,0 };
	int effectID = -1;

	//enemy
	int moveenemy = 0;//0通常,1フックに捕まった,2フックに捕まった後放たれた
	bool helpEnemy = false;
	int mouseAnim = -1;

};
const int PLAYER_NUM = 9;

const int VEGETABLE_TYPE = 8; // 0:キャベツ
const int VEGETABLE_NUM = 5 * VEGETABLE_TYPE;
const int MOUSE_ANIM_NUM = 4;//アニメーションフレーム数

const int ENEMY_NUM = 10;
const int ENEMY_TYPE = 1; // 0:ねずみ

const int BOWL_EFFECT_NUM = 3;


enum HookState {
	FlyingOut,
	Returning,
	Idle
};
