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
	int vegAnimNum = -1;


	//mouse
	bool click = false;
	float timer = 0.0f;
	DxPlus::Vec2 pointer = { 0,0 };
	int effectID = -1;

	//enemy
	int moveenemy = 0;//0通常,1フックに捕まった,2フックに捕まった後放たれた
	bool helpEnemy = false;
	int mouseAnim = -1;

    // --- UFO 用フィールド ---
    bool isUFO = false;
    int ufoLightAnim = 0;
    float ufoLightTimer = 0.0f;

    int ufoVegetableIndex = -1;
    bool ufoHasVegetable = false;

    int ufoDropState = 0; // 0=未,1=ドロップ中,2=上昇退場,3=落下(破壊)
    float ufoDropTimer = 0.0f;
    bool ufoBeingTaken = false;

    // フェード用
    float alpha = 1.0f;      // 1.0 = 不透明, 0.0 = 消失
    bool fading = false;
    float fadeSpeed = 1.0f;  // alpha 減少速度

    // 回転（落下時の回転速度を保持）
    float angularVelocity = 0.0f; // deg/s
};
const int PLAYER_NUM = 11;

const int VEGETABLE_TYPE = 7; // 0:キャベツ
const int VEGETABLE_NUM = 5 * VEGETABLE_TYPE;
const int VEG_ANIM_NUM = 3; //アニメーションフレーム数

const int MOUSE_ANIM_NUM = 4;//アニメーションフレーム数
const int UFO_ANIM_NUM = 3;//アニメーションフレーム数
const int ENEMY_TYPE = 2; // 0:ねずみ
const int ENEMY_NUM = 5 * ENEMY_TYPE;

const int BOWL_EFFECT_NUM = 3;

const int TITLE_BACK_NUM = 5;
const int TITLE_BACKPLAY_NUM = 8;
const int TITLE_BUTTON_NUM = 4;

const int RESULT_ANIM_COUNT = 7;

const int ANI_SOMESHING_NUM = 5;//何かのアニメーション予定


enum HookState {
	FlyingOut,
	Returning,
	Idle
};
