#pragma once
#include "DxPlus/DxPlus.h"

struct Entity2D
{
    //�ʒu�֌W
    DxPlus::Vec2 position = {};
    DxPlus::Vec2 velocity = {};
	float gravity = 0.98f; // �d�͉����x
	float speed = 0.0f;

    //�摜
    int spriteID = -1;
	DxPlus::Vec2 scale = { 1.0f, 1.0f };
	DxPlus::Vec2 center = { 64.0f, 64.0f };
	bool isActive = false;
	int type = 0;
	
	//�t�b�N�Ŏg��
	float angle = 0;
	DxPlus::Vec2 target = {};
	DxPlus::Vec2 HomePositionLeft = {};
	DxPlus::Vec2 HomePositionRight = {};

    //player
    int score = 0;

    //Vegetable
    int havescore = 0;
	float  baseY = {};        // ���
	float JumpPower = 10.0f;



	//mouse
	bool click = false;
	float timer = 0.0f;
	DxPlus::Vec2 pointer = { 0,0 };
	int effectID = -1;

	//enemy
	int BreakScore = 0;
	

};
const int PLAYER_NUM = 9;

const int VEGETABLE_NUM = 12;
const int VEGETABLE_TYPE = 1; // 0:�L���x�c

const int ENEMY_NUM = 6;
const int ENEMY_TYPE = 1; // 0:�˂���




enum HookState {
	FlyingOut,
	Returning,
	Idle
};